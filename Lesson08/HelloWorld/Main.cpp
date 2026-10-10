#include <iostream>
#include <cstring>

#define LOG(x) std::cout << x << std::endl;

int main()
{
    // int var = 8;
    // void* ptr = nullptr;
    // void* ptr = &var;
    // int* ptr = &var;
    // double* ptr = (double*)&var;

    // *ptr = 10;

    // LOG(var);

    char* buffer = new char[8];
    std::memset(buffer, 0, 8);

    char** ptr = &buffer;

    delete[] buffer;

    std::cin.get();
}
