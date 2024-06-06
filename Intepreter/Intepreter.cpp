#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <cctype>

struct MemoryCell {
    std::string name;
    int value;

    MemoryCell(const std::string& n, int v) : name(n), value(v) {}
};

class Interpreter {
private:
    std::unordered_map<std::string, MemoryCell*> variables;
    std::vector<std::unordered_map<std::string, MemoryCell*>> scopes;

    void clearVariables() {
        for (auto& pair : variables) {
            delete pair.second;
        }
        variables.clear();
    }

public:
    Interpreter() {}

    ~Interpreter() {
        clearVariables();
    }

    void interpret(const std::string& code) {
        std::istringstream iss(code);
        std::string line;
        while (std::getline(iss, line, ';')) {
            processLine(line);
        }
    }

private:
    void processLine(const std::string& line) {
        std::istringstream iss(line);
        std::string token;
        std::vector<std::string> tokens;
        while (iss >> token) {
            tokens.push_back(token);
        }

        if (tokens.empty())
            return;

        if (tokens[0] == "print") {
            if (tokens.size() > 1) {
                printVariable(tokens[1]);
            }
            else {
                printAllVariables();
            }
        }
        else if (tokens[0].find('=') != std::string::npos) {
            processAssignment(tokens[0]);
        }
    }

    void processAssignment(const std::string& assignment) {
        size_t equalPos = assignment.find('=');
        std::string varName = assignment.substr(0, equalPos);
        std::string exprStr = assignment.substr(equalPos + 1);

        int result = evaluateExpression(exprStr);

        if (!variables.count(varName)) {
            MemoryCell* newCell = new MemoryCell(varName, result);
            variables[varName] = newCell;
        }
        else {
            variables[varName]->value = result;
        }
    }

    int evaluateExpression(const std::string& exprStr) {
        std::istringstream iss(exprStr);
        std::vector<std::string> tokens;
        std::string token;
        while (iss >> token) {
            tokens.push_back(token);
        }

        return evaluateExpressionHelper(tokens);
    }

    int evaluateExpressionHelper(const std::vector<std::string>& tokens) {
        std::vector<int> values;
        std::vector<char> ops;

        for (const auto& token : tokens) {
            if (isdigit(token[0])) {
                values.push_back(std::stoi(token));
            }
            else if (isalpha(token[0])) {
                values.push_back(variables[token]->value);
            }
            else if (token == "+" || token == "-" || token == "*" || token == "/") {
                ops.push_back(token[0]);
            }
        }

        for (size_t i = 0; i < ops.size(); ++i) {
            if (ops[i] == '*') {
                values[i] = values[i] * values[i + 1];
                values.erase(values.begin() + i + 1);
                ops.erase(ops.begin() + i);
                --i;
            }
            else if (ops[i] == '/') {
                values[i] = values[i] / values[i + 1];
                values.erase(values.begin() + i + 1);
                ops.erase(ops.begin() + i);
                --i;
            }
        }

        int result = values[0];
        for (size_t i = 0; i < ops.size(); ++i) {
            if (ops[i] == '+') {
                result += values[i + 1];
            }
            else if (ops[i] == '-') {
                result -= values[i + 1];
            }
        }

        return result;
    }

    void printVariable(const std::string& varName) {
        if (variables.count(varName)) {
            std::cout << variables[varName]->value << std::endl;
        }
        else {
            std::cerr << "Error: Variable '" << varName << "' is not declared." << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    void printAllVariables() {
        for (auto& pair : variables) {
            std::cout << pair.first << ": " << pair.second->value << std::endl;
        }
    }
};

int main() {
    Interpreter interpreter;
    std::string code = "myvar=15;"
        "ccc=myvar/3;"
        "{"
        "bg=25;"
        "ccc=bg+myvar;"
        "{"
        "param=0;"
        "param=ccc/bg+15;"
        "print param;"
        "}"
        "print ccc;"
        "}"
        "bg=ccc*myvar;"
        "print;";
    interpreter.interpret(code);
    return 0;
}
