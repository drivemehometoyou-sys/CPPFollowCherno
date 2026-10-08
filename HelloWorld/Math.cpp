// #include <iostream>

// #define INTEGER int
// #define INTEGER Zcy

// #if 0
// INTEGER Multiply(int a, int b)
// {
//     int result = a * b;
//     return result;
// // #include "EndBrace.h"
// }
// #endif

//  g++ -S Math.cpp -o Math.asm        
// g++ -S -masm=intel -O0 Math.cpp -o Math.asm

// const char* Log(const char* message)
// {
//     return message;
// }

// // int Multiply(int a, int b)
// int Multiply()
// {
//     Log("nowhere");
//     // return a * b;
//     return 5*2;   // 常数折叠
// // #include "EndBrace.h"
// }

// .cpp .h->预处理->ii->编译->asm->汇编->.o->链接->.exe
//Preprocessing Compilation Assembly Linking

// #include 本质上是预处理阶段的文本包含

// 编译器以翻译单元为单位工作
// 每个 .cpp 经过预处理形成的结果，称为一个翻译单元（Translation Unit）

// 编译器会将 C++ 翻译成机器指令

// 编译器的工作原理： 获取源文件并输出一个obj文件，obj文件是包含机器代码的文件，以及其他我们定义的常数数据
//  C++ 编译器并不是直接把整个项目变成一个 exe，而是先把每个源文件处理成机器能够理解的目标文件，最后再由链接器将它们组合成程序。

#include <iostream>
#include "Log.h"
// void Log(const char* message)
// {
//    std::cout << message << std::endl;
// }

// void Log(const char* message);


static int Multiply(int a, int b)
{
    Log("Multiply");
    return a * b;
}

int main()
{
    std::cout << Multiply(4,3) << std::endl;
    std::cin.get();
}