#include <iostream>
#include <string>
#include <stdlib.h> // 我的环境用不了
#include <cstring>


int main()
{
    // const char name[5] = "Leon";
    // const char name[6] = "Le\0on";
    // std::cout << std::strlen(name) << std::endl; // 2 遇到\0会停

    // char* name = "Leon";  // 现在被禁止了
    // char* name = (char*)"Leon";  // 这样就可以了
    // name[1] = 'f';  // 但仍然无法修改的
    
    // const char* name = "Leon";  // 存在了rdata只读，无法修改
    // // const char* name5 = u8"Leon";  // C++版本问题
    // const char8_t* name6 = u8"Leon";  // utf8

    // const wchar_t* name2 = L"Leon";

    // const char16_t* name3 = u"Leon";   // utf16
    // const char32_t* name4 = U"Leon";   // utf32

    // std::cout << name << std::endl; 



    // std::string name0 = std::string("Leon") + " hello";
    // using namespace std::string_literals;
    // std::string name0 = "Leon"s + " hello";  // 这个s是一个操作符函数
    // std::u32string name0 = U"Leon"s + U" hello"; 

//     const char* example = R"(Line1
// Line2
// Line3
// Line4)"; // 忽略转义字符

//     const char* ex = "Line1\n" 
//         "Line2\n" 
//         "Line3\n" 
//         "Line4\n";   
    
//     std::cout << example << std::endl; 
//     std::cout << ex << std::endl; 


// 字符串字面量永远保存在内存的 只读区域
    char name[] = "Cherno";
    name[2] = 'A';
    std::cout << name << std::endl; 



    std::cin.get();
} 
