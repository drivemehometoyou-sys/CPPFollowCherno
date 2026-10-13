#include <iostream>

// struct Entity
// {
//     int x, y;

//     void Print()
//     {
//         std::cout << x << ", " << y << std::endl;
//     }
// };

struct Entity
{
    // static int x, y;
    int x, y;

    // static void Print()
    // {
    //     std::cout << x << ", " << y << std::endl;
    // }
};


// static void Print()  // 静态方法没有类的实例, 就好比这样
// {
//     std::cout << x << ", " << y << std::endl;
// }

static void Print(Entity e) // 非静态方法，本质上就这样
{
    std::cout << e.x << ", " << e.y << std::endl;
}


// int Entity::x;
// int Entity::y;

int main()
{
    // Entity e;      // 甚至不需要实例， 因我们所做一切均为静态
    // e.x = 2;
    // e.y = 3;
    Entity e;
    e.x = 2;
    e.y = 3;

    // Entity::x = 2;
    // Entity::y = 3;

    // Entity e1 = { 5, 8 };
    // Entity e1;
    // e1.x = 5;
    // e1.y = 8;
// 这两个变量在Entity的所有实例中 只有一个实例
// 因此 这样引用 是没意义的

    Entity e1;
    e1.x = 5;
    e1.y = 8;

   
    // Entity::x = 5;
    // Entity::y = 8;
// 设计目的： 在所有Enitity实例之间共享数据， or将它实际存储在Entity类中是有意义的

    // e.Print();
    // e1.Print();
    // Entity::Print(); // 注意！ 静态方法不能访问 非静态变量, 因为： 静态方法没有类的实例， 就好像在类外写了一个方法

    Print(e);
    Print(e1);


    std::cin.get();
} 
 
