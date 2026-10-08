#pragma once
void Log(const char* message);
// // 还有一种方法：inline：将我们的函数调用替换为 函数体
// static void Log(const char* message)
// // void Log(const char* message)
// {
//     std::cout << message << std::endl;
// }

void Log(const char* message);