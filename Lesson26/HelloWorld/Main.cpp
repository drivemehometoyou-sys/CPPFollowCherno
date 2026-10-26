#include <iostream>
#include <string>

// class Entity
// {
// private:
//     std::string m_Name;

// public:
//     Entity()
//     {
//         m_Name = "Unknown"; 
//     }

//     Entity(const std::string& name)
//     {
//         m_Name = name;
//     }

//     const std::string& GetName()  
//     { 
//         return m_Name; 
//     }
// };



// class Entity
// {
// private:
//     std::string m_Name;
//     int m_Score;
// public:
//     Entity()
//         : m_Name("Unknown"), m_Score(0)  // 成员初始化列表      使用它对性能有很大好处：对于某些类，不用的话会创建两次对象，然后抛弃一次
//     {
//     }

//     Entity(const std::string& name)
//         :m_Name(name)
//     {   
//     }

//     const std::string& GetName()  
//     { 
//         return m_Name; 
//     }
// };

class Example
{
public:
    Example()
    {
        std::cout << "Created Entity!" << std::endl; 
    }
    Example(int x)
    {
        std::cout << "Created Entity with " << x << std::endl; 
    }
};

class Entity
{
private:
    std::string m_Name;
    Example m_Example;
    public:
    // Entity()
    // {
    //     m_Name = "Unknown"; 
    //     m_Example = Example(8);  // 会发现Example被创建了两次
    // }
    Entity()
    : m_Example(8) //正常了
    {
        m_Name = "Unknown";
    }


    Entity(const std::string& name)
        :m_Name(name)
    {   
    }

    const std::string& GetName()  
    { 
        return m_Name; 
    }
};



int main()
{
    // Entity e0;
    // std::cout << e0.GetName() << std::endl;

    // Entity e1("Leon");
    // std::cout << e1.GetName() << std::endl;

    Entity e0;


    std::cin.get();
} 
