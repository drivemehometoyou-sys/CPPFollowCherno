#include <iostream>  // 预处理语句
#include "Log.h"

// void Log(const char* message)
// {
//     std::cout << message << std::endl;
// }

// void Logr(const char* message)
// {
//     std::cout << message << std::endl;
// }

// int Log(const char* message, int level)
// int Log(const char* message)
// {
//     std::cout << message << std::endl;
//     return 0;
// }

void Log(const char* message)
{
    std::cout << message << std::endl;
}


void InitLog()
{
    Log("Initialized Log");
}
