#include "Functions.h" 

int main()
{
    system("color F0");
    std::map<std::string, std::vector<int>> arrays; 
    std::fstream instr("instruction.txt");
    std::string line;
    std::string name;
    std::string name2;
    try
    {
        if (instr.is_open())
        {
            while (std::getline(instr, line))
            {
                std::transform(line.begin(), line.end(), line.begin(), ::toupper);

                if (getWord(line, 0) == "LOAD")
                {
                    Load(name, line, arrays);
                }

                if (getWord(line, 0) == "SAVE")
                {
                    Save(name, line, arrays);  
                }

                if (getWord(line, 0) == "RAND")
                {
                    Rand(name, line, arrays);
                }

                if (getWord(line, 0) == "CONCAT")
                {
                    Concat(name, name2, line, arrays);
                }
                
                if (getWord(line, 0)[0] == 'F')
                {
                    Freee(name, line, arrays);
                }

                if (getWord(line, 0) == "REMOVE")
                {
                    Remove(name, line, arrays);
                }

                if (getWord(line, 0) == "COPY")
                {
                    Copy(name, name2, line, arrays);                    
                }

                if (getWord(line, 0) == "SORT")
                {
                    Sort(name, line, arrays);
                }

                if (getWord(line, 0) == "PERMUTE")
                {
                    Permute(name, line, arrays);
                }

                if (getWord(line, 0) == "INTERSECT")
                {
                    Intersect(name, name2, line, arrays);                 
                }

                if (getWord(line, 0) == "XOR")
                {
                    Xor(name, name2, line, arrays);                    
                }

                if (getWord(line, 0) == "STAT")
                {
                    Stat(name, line, arrays);
                }

                if (getWord(line, 0) == "PRINT" && getWord(line, 2) != "ALL;")
                {
                    Print_from_and_to(name, line, arrays);                   
                }

                if (getWord(line, 0) == "PRINT" && getWord(line, 2) == "ALL;")
                {
                    Print_all(name, line, arrays);
                }
            }
        }
        else
        { 
            throw std::logic_error("File not open"); 
        } 

        instr.close(); 
    } 
    catch (std::logic_error const& ex) 
    { 
        std::cout << ex.what(); 
        return 1; 
    } 
    

    return 0;
}