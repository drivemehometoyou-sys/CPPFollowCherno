#include <iostream>
#include <GLFW/glfw3.h>

int main()
{
    int a = glfwInit();
    std::cout << a << std::endl;
    std::cin.get();
}


// g++ -DGLFW_DLL HelloWorld/Main.cpp -o HelloWorld/Main.exe `
//     -I"Dependencies/GLFW/include" `
//     "Dependencies/GLFW/lib-mingw-w64/libglfw3dll.a" `
//     -lgdi32

//     配置位置	作用
// c_cpp_properties.json 中的 "GLFW_DLL"	 ： 告诉 IntelliSense 定义这个宏
// 编译命令中的 -DGLFW_DLL	                  ：真正告诉 GCC 定义这个宏