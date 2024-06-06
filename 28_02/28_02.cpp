#include <iostream>
#include <string>
#include <ctime>
#include <time.h>
#include <stdio.h>

enum class LogLevel 
{
    INFO,
    WARNING,
    ERROR
};

class Logger
{
public:
    static Logger& getInstance() 
    {
        static Logger instance;
        return instance;
    }

    void log(LogLevel level, const std::string& message) 
    {
        std::string levelStr;
        switch (level) 
        {
        case LogLevel::INFO:
            levelStr = "INFO";
            break;
        case LogLevel::WARNING:
            levelStr = "WARNING";
            break;
        case LogLevel::ERROR:
            levelStr = "ERROR";
            break;
        }

        std::time_t t = std::time(nullptr);
        //std::cout << "[" << std::asctime(std::localtime(&t)) << "] ";
        std::cout << "[" << levelStr << "] " << message << std::endl;
    }

private:
    Logger() {} // Приватный конструктор для синглтона
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
};

int main() 
{
    Logger::getInstance().log(LogLevel::INFO, "This is an information message.");
    Logger::getInstance().log(LogLevel::WARNING, "This is a warning message.");
    Logger::getInstance().log(LogLevel::ERROR, "This is an error message.");

    return 0;
}
