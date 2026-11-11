// #include "../../Engine/src/Engine.h"
#include "Engine.h"
#include <iostream>

int main()
{
    engine::PrintMessage();
    std::cin.get();
}

// 普通多文件编译过程

// PS C:\Users\zhuchaoyang\Desktop\CPPFollowCherno\Lesson40> cd ..\Lesson41                                             
// PS C:\Users\zhuchaoyang\Desktop\CPPFollowCherno\Lesson41> g++ Game/src/Application.cpp Engine/src/Engine.cpp -o Game/Game.exe
// PS C:\Users\zhuchaoyang\Desktop\CPPFollowCherno\Lesson41> .\Game\Game.exe      


// 制作静态库过程

// PS C:\Users\zhuchaoyang\Desktop\CPPFollowCherno\Lesson41> g++ -c Engine/src/Engine.cpp -I"Engine/src" -o build/Engine.o
// PS C:\Users\zhuchaoyang\Desktop\CPPFollowCherno\Lesson41> g++ -c Engine/src/Engine.cpp -I"Engine/src" -o build/Engine.o
// PS C:\Users\zhuchaoyang\Desktop\CPPFollowCherno\Lesson41> ar rcs build/libEngine.a build/Engine.o
// PS C:\Users\zhuchaoyang\Desktop\CPPFollowCherno\Lesson41> ar t build/libEngine.a
// Engine.o
// PS C:\Users\zhuchaoyang\Desktop\CPPFollowCherno\Lesson41> g++ Game/src/Application.cpp `
// >>     -I"Engine/src" `
// >>     build/libEngine.a `
// >>     -o build/Game.exe