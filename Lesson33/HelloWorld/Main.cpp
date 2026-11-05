#include <iostream>



class Entity
{
public:
    Entity()
    {
        std::cout << "Created Entity" << std::endl;
    }

    ~Entity()
    {
        std::cout << "Destroyed Entity" << std::endl;
    }
};

// 这样写是错的
// int* CreateArray()
// {
//     int array[50];
//     return array;
// }

// 作用域指针
class ScopedPtr
{
private:
    Entity* m_Ptr;
public:
    ScopedPtr(Entity* m_Ptr)
        : m_Ptr(m_Ptr)
    {
    }

    ~ScopedPtr()
    {
        delete m_Ptr;
    }
};


void CreateArray(int* array)
{
    // fill our array;
}

int main()
{
    // int* a = CreateArray();
    int array[50];
    CreateArray(array);

    {
        // Entity e;
        // Entity* e = new Entity();
    
        ScopedPtr e = new Entity(); // 这里其实有个隐式转换.可以用explicit测试 
        // ScopedPtr e(new Entity);

    }
    std::cin.get();
} 
