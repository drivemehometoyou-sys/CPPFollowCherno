#include <iostream>
#include <cstring>

class Log
{
public:
    enum Level
    {
        LevelError = 0, LevelWarning, LevelInfo
    };
    // const int LogLevelError = 0;
    // const int LogLevelWarning = 1;
    // const int LogLevelInfo = 2;
private:
    Level m_LogLevel = LevelInfo;  // 使用Level就让m_LogLevel的值限制在enum里面了
public: 
    void SetLevel(Level level)
    {
        m_LogLevel = level;
    }
    
    void Error(const char* message)
    {
        if (m_LogLevel >= LevelError)
            std::cout << "[ERROR]: " << message << std::endl;
    }

    void Warn(const char* message)
    {
        if (m_LogLevel >= LevelWarning)
            std::cout << "[WARNING]: " << message << std::endl;
    }
    
    void Info(const char* message)
    {
        if (m_LogLevel >= LevelInfo)
            std::cout << "[INFO]: " << message << std::endl;
    }
};

int main()
{
    Log log;
    // log.SetLevel(log.LogLevelWarning);
    log.SetLevel(Log::LevelError);  // 这种普通枚举的枚举常量会进入外围作用域，也就是 Log 类的作用域。
    
    log.Warn("Hello!");
    log.Error("Hello!");
    log.Info("Hello!");
    std::cin.get();
} 

