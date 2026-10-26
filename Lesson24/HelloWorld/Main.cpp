#include <iostream>


class Entity
{
private:
    int m_X, m_Y;
    mutable int var;  // 当我们一定要在const方法里面修改变量时候
public:
    int Get_X() const  // 承诺这个方法不能修改类
    { 
        // m_X = 2;
        var = 2; // 被允许修改
        return m_X;
    }

    int Get_X()  
    { 
        // m_X = 2;
        return m_X;
    }

    void Set_X(int x)
    {
        m_X = x;
    }
};


// class Entity
// {
// private:
//     // int* m_X, m_Y;
//     int* m_X, *m_Y;

// public:
//     const int* const Get_X() const   // 意味着我们返回了一个不能修改的指针，指针的内容也不能被修改，这个方法承诺不修改实际的Entity类
//     { 
//         return m_X;
//     }
// };



// // 常量引用的方法，这意味着e是一个常量
// void PrintEntity(const Entity& e)
// {
//     std::cout << e.Get_X() << std::endl; 
// }

// // 这是个指针，我可以修改它的指向, 但不能修改e所指向的内容
// void PrintEntity(const Entity* e)
// {
//     e = nullptr;
//     std::cout << e->Get_X() << std::endl; 
// }
// // 这是个引用，我不能修改e，这与指针的工作方式不同（没有所谓 指针和指针指向的内容本身 之分 ；引用就是内容
// void PrintEntity(const Entity& e)
// {
//     // e = Entity();
//     std::cout << e.Get_X() << std::endl; 
// }

// 这里的const意味着 e可以调用任意的const函数
// 所以最终在类里面定义了俩Get_X  又是 重载 
void PrintEntity(const Entity& e)
{
    std::cout << e.Get_X() << std::endl;  // 此时把类的Get_X方法的const去掉后，发现无法调用该函数了 
}

int main()
{
    // const int MAX_AGE = 90;

    // int* a = new int;
    // const int* a = new int;  // const修饰的是指针指向的内存
    // int* const a = new int;  // const修饰的是指针
    // int const* a = new int;  // const修饰的是指针指向的内存
    // const int* const a = new int;  


    // *a = 2;
    // a = (int*)&MAX_AGE;
    // a = nullptr;
    // std::cout << *a << std::endl; 


    Entity e;



    std::cin.get();
} 
