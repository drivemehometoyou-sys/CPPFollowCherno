#include <iostream>
#include <cstring>

#define LOG(x) std::cout << x << std::endl;

// void Increment(int value)
// {
//     value++;
// }

// void Increment(int* value)
// {
//     (*value)++;
// }
 
void Increment(int& value)
{
    value++;
}

int main()
{
    int a = 5;
    // Increment(a);
    // Increment(&a);
    Increment(a);


    int* ptr = &a;
    int& ref = a; // 引用
    ref = 2;
    
    int b = 3;
    ptr = &b;  // 指针可以改变指向，引用不可以
    *ptr = 1;

    LOG(a);
    LOG(b);

    std::cin.get();
}

// 引用就像是 指针的语法糖
// 它不是一个真实的变量
