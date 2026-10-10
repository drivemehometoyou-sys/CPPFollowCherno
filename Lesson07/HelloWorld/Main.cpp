#include <iostream>
#include "Log.h"

int main()
{

    for (int i = 0; i < 5; i++)
    {
        // if (i % 2 == 0)
        // if (i > 2)
        if ((i+1) % 2 == 0)
            // continue; 
            // break;
            return 0;
        Log("Hello World!");
        std::cout << i << std::endl;
                
    }

    // int i = 0;
    // bool condition = true;
    // for (;condition;)
    // {
    //     Log ("Hello");
    //     i++;
    //     if (!(i < 5))  
    //         condition = false;             
    // }

    // int i = 0;
    // while (i < 5)
    // {
    //     Log ("Hello");
    //     i++;
    // }

    // bool condition = false;
    // do
    // {
    //     Log("Hello");
    // } while(condition);

    std::cin.get();
}
