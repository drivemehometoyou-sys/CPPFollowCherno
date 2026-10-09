#include <iostream>
// #include "Log.h"
#include "Log.h"
#include "Common.h"

int main()
{
    InitLog();
    Log("Hello,World!");
    std::cin.get();
}