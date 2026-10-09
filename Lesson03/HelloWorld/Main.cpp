#include <iostream>

int Multiply(int a, int b)
{
    return a * b;
}

// int Multiply()
// {
//     return 5 * 8;
// }

// void Multiply(int a, int b)
// {
//     std::cout << 5 * 8  << std::endl;
// }

void MultipltAndLog(int a, int b)
{
    int result =  Multiply(a, b);
    std::cout << result << std::endl;
}

int main()
{
    MultipltAndLog(4, 3);
    MultipltAndLog(94, 123);
    MultipltAndLog(9, 12);

    // int result =  Multiply(4,3);
    // std::cout << result << std::endl;
   
    std::cin.get();

    // return 0;
}