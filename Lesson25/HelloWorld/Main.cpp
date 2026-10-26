#include <iostream>
#include <string>

class Entity
{
private:
    std::string m_Name;
    mutable int m_DebugCount = 0;
public:
    const std::string& GetName() const 
    { 
        m_DebugCount++;
        return m_Name; 
    }
};


int main()
{
    const Entity e;
    e.GetName();  // 如果把方法后面的const去掉，就无法调用该方法

    int x =8;
    // auto f = [=]()
    // {
    //     int y = x;
    //     y++;
    //     std::cout << x << std::endl;
    // }; // 没法直接x++
    auto f = [=]() mutable
    {
        x++;
        std::cout << x << std::endl;
    };



    f();

    std::cin.get();
} 
