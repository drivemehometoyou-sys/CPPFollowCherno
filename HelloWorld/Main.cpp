#include <iostream>  // 预处理语句

void Log(const char* message);

int main() 
{
    Log("Hello,World!");
    // std::cout << "Hello, World!" << std::endl;  // 1.<<其实是一个函数  2.将字符串推送到cout流中，然后打印到终端，然后推送一个行结束符
    // std::cout.print("Hello,World!").print("Hello,World!");
    std::cin.get();
}
