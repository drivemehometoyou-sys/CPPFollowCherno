#include <iostream>
#include <string>

// void PrintString(std::string string) // 这样子实际上是复制了类（对象，对象在栈上，字符数据却可能得复制在堆上，这样很慢
// {
//     // string += "h"; // 不会影响到传递到原始的字符串
//     std::cout << string << std::endl;
// }

// 所以在只读的情况下，用 常量引用 来传递它
void PrintString(const std::string& string) 
{
    std::cout << string << std::endl;
}


int main()
{
    // char* name = "Leon"; // 现在的C++标准不许这样写

    // const char* name = "Leon"; // // 末尾有一个00(ASCII码)，可以让指针name知道何时停止
    std::string name = "Leon";
    PrintString(name);
    // name.size();       // 如果是char数组，就得strlen，strcpy
    // std::string name = "Leon" + "hello"; // 在这里，它们会转换为指向首字符的指针，而 C++ 不允许两个指针相加。
    
    name += " Hello!"; // 会将 " Hello!" 的字符内容追加到 name 中
    std::string name = std::string("Leon") + "hello";  // 转成两个字符串相加
    
    bool contains = name.find("no") != std::string::npos;
    
    // delete[] name;  // 不可以，并不是创建在堆上
    // name[2] = 'a'; // 不可以，因为const


    char name2[5] = "Leon"; // 自动初始化末尾有一个00
    name2[2] = 'a'; // 可以
    
    char name3[4] = {'L', 'e', 'o', 'n'}; // 不知道何时终止了
    char name4[5] = {'L', 'e', 'o', 'n', 0}; 
    char name5[5] = {'L', 'e', 'o', 'n', '\0'}; 


    std::cout << name << std::endl;
    std::cout << name2 << std::endl;
    std::cout << name3 << std::endl;
    std::cout << name4 << std::endl;
    std::cout << name5 << std::endl;


    std::cin.get();
} 

// int main()
// {
//     // 错误：两个字符串字面量不能直接相加
//     // std::string name = "Leon" + "hello";

//     // 正确：std::string 对象 + C 风格字符串
//     std::string name = std::string("Leon") + "hello";
//     std::cout << name << '\n';

//     // 正确：向已有的 std::string 对象追加内容
//     name += " Hello!";
//     std::cout << name << '\n';
// }