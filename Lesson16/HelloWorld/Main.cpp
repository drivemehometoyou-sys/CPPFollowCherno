#include <iostream>

class Entity
{
public:
    float X, Y;

    // Entity  // 默认的构造函数
    // {

    // }

    Entity()  // 构造函数
    {
        X = 0.0f;
        Y = 0.0f;
        std::cout << "Created Entity" << std::endl;
    }

    Entity(float x, float y)  // 拥有相同的名字， 但参数必须不同   函数重载
    {
        X = x;
        Y = y;
    }
    // void Init()
    // {
    //     X = 0.0f;
    //     Y = 0.0f;
    // }
    
    ~Entity() // 析构函数   
    {
        std::cout << "Destroyed Entity!" << std::endl; 
    }
    
    void Print()
    {
        std::cout << X << ", " << Y << ", " << std::endl;
    }
};

class Log
{

public:
    // Log() = delete;  // 删去默认构造函数， 将导致无法实例化对象

    static void Write()
    {

    }
};


// 展示 栈中对象被销毁时，析构函数发挥作用
void Function()
{
    Entity e;
    e.Print();
}


int main()
{
    // Entity e;
    // // e.Init();
    // std::cout << e.X << std::endl;
    // e.Print();
 
    // Entity e1(5.0f,8.0f);      // 构造函数如果不实例化对象， 将不会运行 比如使用一个类的静态方法
    // // e1.Init();
    // std::cout << e1.X << std::endl;
    // e1.Print();


    // Log::Write();
    // Log l;        // 构造函数不存在，则无法实例化对象

    Function();

    std::cin.get();
} 


