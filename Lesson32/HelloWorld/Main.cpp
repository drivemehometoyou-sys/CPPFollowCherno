#include <iostream>
#include <string>

// void PrintEntity(Entity* e);
void PrintEntity(const Entity& e);

class Entity
{
public:
    int x, y;

    Entity(int x, int y)
    {
        this->x = x;
        this->y = y;
        
        Entity& e = *this;          // 在非const方法里面，可以直接赋值给Entity&
        
        // PrintEntity(this);
        PrintEntity(*this);
    
        
        // (*this).x = x;

        // Entity* e = this;

        // // this = nullptr; // 错误 ， this 其实是const的，即指针的值不可变
        // e->x = x;
    }

    int GetX() const
    {
        // const Entity* e = this; 
        const Entity& e = *this;    // 在const方法里面，this 的类型是 const Entity*

        return x;
    }
};

// void PrintEntity(Entity* e)
// {
//     // Printing
// }

void PrintEntity(const Entity& e)
{
    // Printing
}

int main()
{

    std::cin.get();
} 

//`this` 是 C++ 非静态成员函数中隐含的特殊指针，指向当前调用该函数的对象。
//通过 `this->` 可以访问当前对象的成员，`*this` 则表示当前对象本身，二者分别对应对象地址和对象本身。

//在普通成员函数中，`this` 的类型是 `Entity*`；
//在 const 成员函数中，类型是 `const Entity*`，因此不能通过它修改对象的普通非 mutable 成员。

//此外，可以通过 `this` 或 `*this` 将当前对象的地址或对象本身传递给其他函数，分别对应指针传递和引用传递。

//这节课的核心就是理解 this 与当前对象的关系，以及 const 如何影响 this 的类型和访问权限。