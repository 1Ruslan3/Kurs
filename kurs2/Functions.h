#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdlib> 
#include <ctime> 
#include <cmath>
#include <map>
#include <algorithm>
#include <random>
#include <unordered_set>
#include <unordered_map>

void createArray(std::string& name, std::map<std::string, std::vector<int>> arrays)
{
    arrays[name] = std::vector<int>();
}

std::string getWord(const std::string& str, size_t index)
{
    std::istringstream iss(str);
    std::string word;

    for (auto i = 0; i < index + 1; ++i)
    {
        iss >> word;
    }

    return word;
}

void Load(std::string& name, std::string& line, std::map<std::string, std::vector<int>>& arrays)
{
    auto filePath = getWord(line, 2);
    std::transform(filePath.begin(), filePath.end(), filePath.begin(), ::tolower);
    name = getWord(line, 1);
    name.pop_back();
    filePath.pop_back();
    createArray(name, arrays);
    std::ifstream file(filePath);


    if (!file.is_open())
    {
        throw std::logic_error("File not open");
    }

    std::string num;
    while (file >> num)
    {
        try
        {
            size_t idx;
            auto value = std::stoi(num, &idx);
            if (idx != num.length())
            {
                throw std::invalid_argument("invalid value string representation");
            }
            arrays[name].push_back(value);
        }
        catch (std::invalid_argument const& ex)
        {
            throw std::logic_error("Invalid value of integer from input file!");
        }
    }

    file.close();

    /*for (auto n : arrays[name])
    {
        std::cout << n << " ";
    }*/
}

void Save(std::string& name, std::string& line, std::map<std::string, std::vector<int>>& arrays)
{
    name = getWord(line, 1);
    name.pop_back();
    if (arrays[name].empty() != true)
    {
        auto lexem = getWord(line, 2);
        std::transform(lexem.begin(), lexem.end(), lexem.begin(), ::tolower);
        lexem.pop_back();

        std::ofstream file_output(lexem);

        if (!file_output.is_open())
        {
            throw std::logic_error("File not open");
        }

        for (auto n : arrays[name])
        {
            file_output << n << " ";
        }
        file_output.close();
    }
    else
    {
        throw std::logic_error("Array is empty");
    }
}

void Rand(std::string& name, std::string& line, std::map<std::string, std::vector<int>>& arrays)
{
    name = getWord(line, 1);
    name.pop_back();
    createArray(name, arrays);

    auto count = getWord(line, 2);
    auto lb = getWord(line, 3);
    auto rb = getWord(line, 4);

    count.pop_back();
    lb.pop_back();
    rb.pop_back();

    size_t c, l, r;
    auto count_ = std::stoi(count, &c);
    if (c != count.length())
    {
        throw std::invalid_argument("invalid value string representation");
    }
    auto lb_ = std::stoi(lb, &l);
    if (l != lb.length())
    {
        throw std::invalid_argument("invalid value string representation");
    }
    auto rb_ = std::stoi(rb, &r);
    if (r != rb.length())
    {
        throw std::invalid_argument("invalid value string representation");
    }

    srand(static_cast<unsigned int>(time(nullptr)));

    for (int i = 0; i < count_; ++i)
    {
        arrays[name].push_back(rand() % rb_ + lb_);
    }

    for (auto n : arrays[name])
    {
        std::cout << n << " ";
    }
}

void Concat(std::string& name, std::string& name2, std::string& line, std::map<std::string, std::vector<int>>& arrays)
{
    name = getWord(line, 1);
    name.pop_back();
    name2 = getWord(line, 2);
    name2.pop_back();


    if (arrays[name].empty() != true || arrays[name2].empty() != true)
    {
        arrays[name].insert(arrays[name].end(), arrays[name2].begin(), arrays[name2].end());
    }
    else
    {
        throw std::logic_error("Arrays is empty!");
    }

    for (auto n : arrays[name])
    {
        std::cout << n << " ";
    }
}

void Freee(std::string& name, std::string& line, std::map<std::string, std::vector<int>>& arrays)
{
    name = getWord(line, 0)[5];
    if (arrays[name].empty() != true)
    {
        arrays[name].clear();
    }
    else
    {
        throw std::logic_error("Array is empty");
    }
    for (auto n : arrays[name])
    {
        std::cout << n << " ";
    }
}

void Remove(std::string& name, std::string& line, std::map<std::string, std::vector<int>>& arrays)
{
    name = getWord(line, 1);
    name.pop_back();
    auto index_ = getWord(line, 2);
    index_.pop_back();
    auto count_ = getWord(line, 3);
    count_.pop_back();

    size_t i1, i2;
    auto index = std::stoi(index_, &i1);
    if (i1 != index_.length())
    {
        throw std::invalid_argument("invalid value string representation");
    }
    auto count = std::stoi(count_, &i2);
    if (i2 != count_.length())
    {
        throw std::invalid_argument("invalid value string representation");
    }


    if (arrays[name].empty() != true && arrays[name].size() + index >= count)
    {
        arrays[name].erase(arrays[name].begin() + index, arrays[name].begin() + index + count);
    }
    else
    {
        throw std::logic_error("Cannot remove array elements");
    }
    for (auto n : arrays[name])
    {
        std::cout << n << " ";
    }
}

void Copy(std::string& name, std::string& name2, std::string& line, std::map<std::string, std::vector<int>>& arrays)
{
    name = getWord(line, 1);
    name.pop_back();

    name2 = getWord(line, 4);
    name2.pop_back();

    auto beginIndex_ = getWord(line, 2);
    beginIndex_.pop_back();

    auto endIndex_ = getWord(line, 3);
    endIndex_.pop_back();

    size_t b, e;
    auto beginIndex = std::stoi(beginIndex_, &b);
    if (b != beginIndex_.length())
    {
        throw std::invalid_argument("invalid value string representation");
    }
    auto endIndex = std::stoi(endIndex_, &e);
    if (e != endIndex_.length())
    {
        throw std::invalid_argument("invalid value string representation");
    }

    if (arrays[name].size() - 1 >= endIndex)
    {
        auto beginIter = arrays[name].begin() + beginIndex;
        auto endIter = arrays[name].begin() + endIndex;

        std::copy(beginIter, endIter, std::back_inserter(arrays[name2]));
    }
    else
    {
        throw std::logic_error("There are not enough elements in the array");
    }
    for (auto n : arrays[name2])
    {
        std::cout << n << " ";
    }
}

void Sort(std::string& name, std::string& line, std::map<std::string, std::vector<int>>& arrays)
{
    name = getWord(line, 1);
    name.pop_back();
    char order = name.back();
    name.pop_back();
    if (arrays[name].empty() != true)
    {

        if (order == '+')
        {
            std::sort(arrays[name].begin(), arrays[name].end());
        }
        else if (order == '-')
        {
            std::sort(arrays[name].begin(), arrays[name].end(), std::greater<int>());
        }
    }
    else
    {
        throw std::logic_error("Array is empty");
    }
    for (auto n : arrays[name])
     {
        std::cout << n << " ";
     }
}

void Permute(std::string& name, std::string& line, std::map<std::string, std::vector<int>>& arrays)
{
    name = getWord(line, 1);
    name.pop_back();

    if (arrays[name].empty() != true)
    {
        std::random_device rd;
        std::mt19937 rng(rd());

        std::shuffle(arrays[name].begin(), arrays[name].end(), rng);
    }
    else
    {
        throw std::logic_error("Array is empty");
    }
    for (auto n : arrays[name])
    {
        std::cout << n << " ";
    }
}

void Intersect(std::string& name, std::string& name2, std::string& line, std::map<std::string, std::vector<int>>& arrays)
{
    name = getWord(line, 1);
    name.pop_back();

    name2 = getWord(line, 2);
    name2.pop_back();

    std::vector<int> result;


    std::unordered_set<int> setB(arrays[name2].begin(), arrays[name2].end());


    for (auto n : arrays[name])
    {
        if (setB.find(n) != setB.end())
        {
            result.push_back(n);
        }
    }

    for (auto n : result)
    {
        std::cout << n << " ";
    }
}

void Xor(std::string& name, std::string& name2, std::string& line, std::map<std::string, std::vector<int>>& arrays)
{
    name = getWord(line, 1);
    name.pop_back();

    name2 = getWord(line, 2);
    name2.pop_back();

    // Преобразуем вектор B в unordered_set для быстрого поиска
    std::unordered_set<int> setB(arrays[name2].begin(), arrays[name2].end());

    // Находим симметрическую разность и сохраняем в векторе A
    arrays[name].erase(std::remove_if(arrays[name].begin(), arrays[name].end(), [&](int x) { return setB.find(x) != setB.end(); }), arrays[name].end());

    std::for_each(arrays[name2].begin(), arrays[name2].end(), [&](int x) { if (setB.find(x) == setB.end()) arrays[name].push_back(x); });

    for (auto n : arrays[name])
    {
        std::cout << n << " ";
    }
}

void Stat(std::string& name, std::string& line, std::map<std::string, std::vector<int>>& arrays)
{
    name = getWord(line, 1);
    name.pop_back();

    int size = arrays[name].size();

    int minValue = *std::min_element(arrays[name].begin(), arrays[name].end());
    int maxValue = *std::max_element(arrays[name].begin(), arrays[name].end());

    int minIndex = std::distance(arrays[name].begin(), std::min_element(arrays[name].begin(), arrays[name].end()));
    int maxIndex = std::distance(arrays[name].begin(), std::max_element(arrays[name].begin(), arrays[name].end()));


    std::unordered_map<int, int> frequency;
    for (int num : arrays[name])
    {
        frequency[num]++;
    }


    auto max_freq_it = std::max_element(frequency.begin(), frequency.end(), [](const auto& a, const auto& b)
        {
            return a.second < b.second;
        });
    int mostFrequent = max_freq_it->first;

    double sum = 0;
    for (int num : arrays[name])
    {
        sum += num;
    }
    int average = sum / arrays[name].size();

    double maxDeviation = 0;
    for (int num : arrays[name])
    {
        maxDeviation = std::max(maxDeviation, static_cast<double>(std::abs(num - average)));
    }


    std::cout << "SIZE: " << size << std::endl;
    std::cout << "Min Value: " << minValue << " and its index: " << minIndex << std::endl;
    std::cout << "Max Value: " << maxValue << " and its index: " << maxIndex << std::endl;
    std::cout << "Most Frequent: " << mostFrequent << std::endl;
    std::cout << "Average: " << average << std::endl;
    std::cout << "Max Deviation: " << maxDeviation << std::endl;

}

void Print_from_and_to(std::string& name, std::string& line, std::map<std::string, std::vector<int>>& arrays)
{
    name = getWord(line, 1);
    name.pop_back();

    auto start_ = getWord(line, 2);
    start_.pop_back();

    auto stop_ = getWord(line, 3);
    stop_.pop_back();

    size_t st, sp;
    auto start = std::stoi(start_, &st);
    if (st != start_.length())
    {
        throw std::invalid_argument("invalid value string representation");
    }
    auto stop = std::stoi(stop_, &sp);
    if (sp != stop_.length())
    {
        throw std::invalid_argument("invalid value string representation");
    }

    if (arrays[name].size() - 1 >= stop && arrays[name].empty() != true)
    {
        for (int i = start; i < stop && i < arrays[name].size(); ++i)
        {
            std::cout << arrays[name][i] << " ";
        }
    }
    else
    {
        throw std::logic_error("There are not enough elements in the array");
    }
}

void Print_all(std::string& name, std::string& line, std::map<std::string, std::vector<int>>& arrays)
{
    name = getWord(line, 1);
    name.pop_back();

    if (arrays[name].empty() != true)
    {
        for (auto n : arrays[name])
        {
            std::cout << n << " ";
        }
    }
    else
    {
        throw std::logic_error("Array is empty");
    }
}