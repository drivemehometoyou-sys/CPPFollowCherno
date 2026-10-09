#include <iostream>  


int main() 
{
    // char, short, int, long, long long
    // unsigned char, short, int, long, long long

    // char a = 'A';
    // char a = 65;

    // short a = 65;
    // std::cout << a << std::endl;
    // std::cin.get();

    // float variable = 5.5; // double
    // float variable = 5.5f; // 4bytes
    // double var = 5.2;

    // bool variable = true;
    bool variable = false;   // 1byte  因为需要寻址
    std::cout << sizeof(bool) << std::endl;
    std::cout << sizeof(int) << std::endl;


    // int variable = 8;    // 4bytes  -21b ~ 21b
    // unsigned int variable = 8; // 42b
    // std::cout << variable << std::endl;
    // variable = 20;
    // std::cout << variable << std::endl;
    std::cin.get();
}