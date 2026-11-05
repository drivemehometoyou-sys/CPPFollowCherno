#include <iostream>
#include <string>
#include <cstring>

struct Vector2
{
    float x, y;
};

class String
{
private:
    char* m_Buffer;
    unsigned int m_Size;
public:
    String(const char* string)
    {
        m_Size = std::strlen(string);
        m_Buffer = new char[m_Size + 1]; 
        memcpy(m_Buffer, string, m_Size);
        m_Buffer[m_Size] = 0;

        // for(int i = 0; i < m_Size; i++)
        //     m_Buffer[i] = string[i];
    }  

    // // CPP会默认提供一个拷贝构造函数，所做的是：内存复制，将other对象的内存浅拷贝进这些成员变量
    // String(const String& other)   // 给这个加explict,会发现下面 String second = string; 浅拷贝 无法使用
    //     :m_Buffer(other.m_Buffer), m_Size(other.m_Size)
    // {   
    // }
    // String(const String& other) = delete;

    String(const String& other)   // 深拷贝
        : m_Size(other.m_Size)
    {
        std::cout << "Copied String" << std::endl;
        m_Buffer = new char[m_Size + 1];
        memcpy(m_Buffer, other.m_Buffer, m_Size + 1);
    }

    ~String()
    {
        delete[] m_Buffer;
    }

    char& operator[](unsigned int index)
    {
        return m_Buffer[index];
    }

    friend std::ostream& operator<<(std::ostream& stream, const String& string);
};

std::ostream& operator<<(std::ostream& stream, const String& string)
{
    // stream << string.GetBuff();
    stream << string.m_Buffer;
    return stream;
}


// void PrintString(String string)   // 这里也会发生 深拷贝
// {
//     std::cout << string << std::endl;
// }

void PrintString(const String& string)   
{
    String copy = string;   // 如果我们真的需要 复制
    std::cout << string << std::endl;
}

int main()
{
    // Vector2 a = {2, 3};
    // Vector2 b = a;
    // b.x = 4;
    
    // Vector2* a = new Vector2();
    // Vector2* b = a;
    // b->x = 2;

    String string = "Leon"; // 隐式转换
    String second = string; 
    // 程序最后会崩溃，因为这里是 浅拷贝，对char* m_Buffer进行了复制,两个String里面的这个指针指向的同一片内存，析构delete了两次

    second[2] = 'a';    // string.operator[](2);
    // 可以看到两个Lean
    // std::cout << string << std::endl;
    // std::cout << second << std::endl;   

    PrintString(string);
    PrintString(second); // 如果是深拷贝版本PrintString，则会输出 Copied String

    std::cin.get();
} 
