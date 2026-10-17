#include <iostream>

enum Example : unsigned char
{
    A, B, C
//  0  1  2

    // A = 0, B = 4, C = 3

    // A = 3, B, C
}; // 这里面的数只能是 整数

int main()
{

    Example value = B;

    if (value == 1)
    {

    }

    std::cin.get();
} 


