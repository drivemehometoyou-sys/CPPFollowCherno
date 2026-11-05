#include <iostream>
#include <string>
#include <memory>

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

    void Print() {}   
};


int main()
{
//     {
//         std::unique_ptr<Entity> entity(new Entity());  // unique_ptr的构造函数是explicit的
//         std::unique_ptr<Entity> entity1 = std::make_unique<Entity>();    
    
//         // std::unique_ptr<Entity> entity0 = entity1;  // 禁止拷贝构造函数和拷贝构造操作符
//         // 它们都可能导致两个智能指针同时拥有同一个动态对象，从而产生重复释放的问题。

//         std::shared_ptr<Entity> sharedEntity = std::make_shared<Entity>();
//         // std::shared_ptr<Entity> sharedEntity1(new Entity());  // 不推荐这种写法
//         // make_shared 把原本分开分配的 Entity 对象和 shared_ptr 控制块合并到一次内存分配中。
//         std::shared_ptr<Entity> e0 = sharedEntity;
//         std::shared_ptr<Entity> e1 = sharedEntity;


//         entity1->Print();
//     }

    {
        std::shared_ptr<Entity> e0;
        {
            std::shared_ptr<Entity> sharedEntity = std::make_shared<Entity>();
            e0 = sharedEntity;
        }
    }  // 到这里，对象才会被销毁 

    
    {
        std::weak_ptr <Entity> e0;  //weak_ptr 不增加计数
        {
            std::shared_ptr<Entity> sharedEntity = std::make_shared<Entity>();
            e0 = sharedEntity;
        }   // 到这里，对象就会被销毁
    }  

    std::cin.get();
} 

// C++ 智能指针解决的是动态对象的生命周期管理问题。

// unique_ptr 通过独占所有权管理对象，
// shared_ptr 通过引用计数实现共享所有权，
// 而 weak_ptr 提供不参与所有权管理的观察机制。

// 三者共同利用 RAII 思想，减少手动管理内存造成的错误。