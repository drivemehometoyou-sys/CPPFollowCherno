#include <iostream>

class Entity
{
public:
    float X, Y;

    void Move(float xa, float ya)
    {
        X += xa;
        Y += ya;
    }
};

class Player : public Entity   // 继承
{
public:
    const char* Name;

    void PrintName()
    {
        std::cout << Name << std::endl; 
    }
};


// class Player
// {
// public:
//     const char* Name;
//     float X, Y;

//     void Move(float xa, float ya)
//     {
//         X += xa;
//         Y += ya;
//     }

//     void PrintName()
//     {
//         std::cout << Name << std::endl; 
//     }
// };

int main()
{
    std::cout << sizeof(Entity) << std::endl; 
    std::cout << sizeof(Player) << std::endl; 

    Player player;
    player.Name = "Leon";
    player.PrintName();
    player.Move(5, 5);    
    std::cin.get();
} 


