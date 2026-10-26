#include <iostream>

class Entity
{
public:
    // std::string GetName() { return "Entity"; }
    virtual std::string GetName() { return "Entity"; }  //此时通过基类指针调用 GetName()，程序会根据对象的实际动态类型决定执行哪个版本。

};

class Player : public Entity
{
private:
    std::string m_Name;
public:
    Player(const std::string& name)
    : m_Name(name) {}

    // std::string GetName() { return m_Name; }  
    std::string GetName() override { return m_Name; }  // override 非必须， 但能增加 可读性
};

void PrintName(Entity* entity)
{
    std::cout << entity->GetName() << std::endl; 
}

int main()
{
    Entity* e = new Entity();
    std::cout << e->GetName() << std::endl;
    Player* p = new Player("Leon");
    std::cout << p->GetName() << std::endl;
    
    // Entity* entity = p;
    // std::cout << entity->GetName() << std::endl; // 打印出来是 Entity

    PrintName(e); 
    PrintName(p); // 打印出来是 Entity， 加了virtual后是 Leon
    
    // Entity原因：编译器依据指针的静态类型 Entity*，选择调用 Entity::GetName()

    std::cin.get();
} 

// 向上转型：让 Player* 能够作为 Entity* 使用。
// 动态多态：让 Entity* 调用虚函数时，执行实际对象对应的重写版本。
// PrintName(p) 隐式完成向上转型；entity->GetName() 借助 virtual 实现动态多态。


// 虚函数是由开销的： 1. 需要额外的内存来存储V表，基类中要有一个指针指向V表 
//                 2. 每次调用虚函数的时候，我们需要遍历V表，来确定要映射到哪个函数