#include <iostream>
#include <string>

using String = std::string;

class Entity
{
private:
    String m_Name;
    int m_Age;
public:
    explicit Entity(const std::string& name)
        : m_Name(name), m_Age(-1) {}

    explicit Entity(int age)  // explicit ：禁用隐式转换
        : m_Name("Unknown"), m_Age(age) {}
};

void PrintEntity(const Entity& entity)
{
    //Printing
}


int main()
{
    // 隐式构造函数
    //Implicit Conversion 隐式转换

    PrintEntity(22);
    // PrintEntity("Leon");
    PrintEntity((std::string)"Leon");
    PrintEntity(Entity("Leon"));

    Entity a("Leon"); 
    // Entity a1 = "Leon";       
    // Entity a1 = Entity("Leon");
    Entity a1 = (std::string)"Leon";

    Entity b = 23;
    Entity b1(23);
    Entity b2 = Entity(23);
    Entity b3 = (Entity)23;

    std::cin.get();
} 
