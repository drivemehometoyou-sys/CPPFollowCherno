#include <iostream>
#include <string>

using String = std::string;

class Entity
{
private:
    String m_Name;
public:
    Entity() : m_Name("Unknown") {}
    Entity(const String& name) : m_Name(name) {}

    ~Entity()
    {
        std::cout << "Entity destroyed!" << std::endl;
    }

    const String& GetName() const { return m_Name; }
};

void Function()
{

}

int main()
{
    int a;
    // int* b = new int;
    int* b = new int[50];
    
    // Entity* e = new Entity[50];
    
    // Entity* e = new Entity();  // 区别：执行了Entity构造函数
    // Entity* e = (Entity*)malloc(sizeof(Entity));
    
    Entity* e = new(b) Entity;
    
    delete e;  // // 区别：执行了Entity析构函数
    // free(e);
    delete[] b;

    std::cin.get();
} 
