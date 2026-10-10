#include <iostream>
#include "Log.h"

int main()
{
    int x = 6;
    // bool comparisonResult = x == 5;
    // if(comparisonResult)
    // {
    //     Log("Hello,World!");
    // }
    // if (x == 5)
    //     Log("Hello,World!");
    // if (x)
    // {   
    //     /* code */
    // }
    
    const char* ptr = "Hello";
    // const char* ptr = nullptr;
    if(ptr)
        Log(ptr);
    else if (ptr == "Hello") // 这部分永远不会被执行
        Log("Hello");               
    else
        Log("Ptr is null");
    std::cin.get();
}

// else if (condition)
// {
//     /* code */
// }
// =
// else
// {
//     if

// }
