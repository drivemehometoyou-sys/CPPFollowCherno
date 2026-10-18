#include <iostream>

class Printable   // interface
{
public:
    virtual std::string GetClassName() = 0; 
};

class Entity : public Printable
{
public:
    virtual std::string GetName() { return "Entity"; }
    std::string GetClassName() override { return "Entity"; }
};

// class Entity  
// {
// public:
//     virtual std::string GetName() = 0; // 使其成为纯虚函数

// };

class Player : public Entity
{
private:
    std::string m_Name;
public:
    Player(const std::string& name)
    : m_Name(name) {}

    std::string GetName() override { return m_Name; }
    // std::string GetClassName() override { return "Player"; }
    std::string GetClassName() override { return "Player"; }

};

void PrintName(Entity* entity)
{
    std::cout << entity->GetName() << std::endl; 
}

class A : public Printable
{
    public:
    std::string GetClassName() override { return "A"; }
};

void Print(Printable* obj)
{
    std::cout << obj->GetClassName() << std::endl;
}

// 意义： 如果确保类都有一个特定的方法，那么就可以将这个类（抽象基类）作为参数（类型）放入一个通用的函数中，然后调用这个方法或者做别的事 

int main()
{
    // Entity* e = new Entity();  // 因为纯虚函数，无法再实例化
    // Entity* e = new Player("");  // 可以实例化，因为在Player里面实现了那个纯虚函数
    
    // Player* p = new Player("Leon");

    Entity* e = new Entity(); // 无法实例化
    Player* p = new Player("Leon"); // 也无法实例化
    // 实现了纯虚函数即可

    // PrintName(e); 
    // PrintName(p); 
    Print(e);
    Print(p);    

    Print(new A());

    std::cin.get();
} 
