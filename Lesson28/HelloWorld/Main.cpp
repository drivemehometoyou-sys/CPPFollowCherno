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
    int a = 2;
    Entity entity = Entity("Leon");  // 生存期就到下面的}
}

int main()
{
    // Entity entity = Entity("Leon");  // 生存期就是所在的main函数
    // std::cout << entity.GetName() << std::endl;

    // Entity* e;
    // {
    //     Entity entity("Leon");
    //     e = &entity;
    //     std::cout << entity.GetName() << std::endl;   
    // }  // 离开这里，这个entity就被销毁

    Entity* e;
    {
        Entity* entity = new Entity("Leon");
        e = entity;
        std::cout << (*entity).GetName() << std::endl;   
    }
    
    delete e;

     std::cin.get();
} 

//如果 对象很大 or 可控生存周期，就选择在堆上吧 否则就 栈 更简单（自动化 且 快