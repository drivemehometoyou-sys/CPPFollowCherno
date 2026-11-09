#include <iostream>
#include <string>

class Entity
{
public:
    int x;
public:
    void Print() const { std::cout << "Hello!" << std::endl; }
};

class ScopedPtr
{
private:
    Entity* m_Obj;
public:
    ScopedPtr(Entity* entity)
        :m_Obj(entity) 
    {
    }

    ~ScopedPtr()
    {
        delete m_Obj;
    }

    const Entity* operator->() const 
    { 
        return m_Obj; 
    }
    
    Entity* operator->() 
    { 
        return m_Obj; 
    }
    // Entity* GetObj() { return m_Obj; }
};

struct Vector3
{
    float x, y, z;
};

int main()
{
    // Entity e;
    // e.Print();

    // Entity* ptr = &e;
    // ptr->Print();
    // ptr->x = 2;

    const ScopedPtr entity = new Entity();  // const 修饰的是整个 ScopedPtr 对象，不允许entity = anotherScopedPtr; const 对象只能调用 const 成员函数
    // entity.GetObj()->Print();
    entity->Print();    // 重载了->
    // entity->->Print();普通运算符重载通常是调用函数并使用其返回值；而 operator-> 比较特殊，编译器会自动继续对返回值应用箭头运算符。

    // 这个写法32位系统可以，64不行 一个指针有 64 位，而 int 只有 32 位。
    // int offsetX = (int)&((Vector3*)nullptr)->x;
    // int offsetY = (int)&((Vector3*)nullptr)->y;
    // int offsetZ = (int)&((Vector3*)nullptr)->z;
    
    // std::cout << offsetX << std::endl;
    // std::cout << offsetY << std::endl;
    // std::cout << offsetZ << std::endl;

    std::cin.get();
}
