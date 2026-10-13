#include <iostream>

// 单例类： 对于某个类，在程序中只允许存在一个实例，并提供统一的访问方式。

// class Singleton // 使用静态指针
// {
// private:
//     static Singleton* s_Instance;
// public:
//     static Singleton& Get() { return *s_Instance; }

//     void Hello() {}
// };

// Singleton* Singleton::s_Instance = nullptr;


class Singleton // 使用函数内局部静态对象
{
public:
    static Singleton& Get() 
    { 
        static Singleton instance;
        return instance; 
    }

    void Hello() 
    {
    }
};
//利用静态成员函数提供统一访问入口，再利用局部静态变量的生命周期特性，让所有调用者都访问同一个对象。


// int i = 0; //这样不好
// void Function()
// {
//     // int i = 0;
//     static int i = 0; // 其实就好比声明了一个全局变量; 但全局变量会在任何位置都能被修改，影响了作用域 加上static后作用域只在此函数内
//     i++;
//     std::cout << i << std::endl;
// } 

int main()
{
    // Function();
    // Function();
    // // i = 10;
    // Function();
    // Function();
    // Function();
    
    Singleton::Get().Hello();  // 单例模式提供了一种统一的访问入口

    std::cin.get();
} 


