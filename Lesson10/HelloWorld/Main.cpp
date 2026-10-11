#include <iostream>
#include <cstring>

#define LOG(x) std::cout << x << std::endl;

// class Player
// {
// public:
//     int x, y;
//     int speed;
    
//     void Move(int xa, int ya)
//     {
//         x += speed * xa;
//         y += speed * ya;
//     }
// };
     
struct Player
{

    int x, y;
    int speed;
    
    void Move(int xa, int ya)
    {
        x += speed * xa;
        y += speed * ya;
    }
};

// void Move(Player& player, int xa, int ya)
// {
//     player.x += player.speed * xa;
//     player.y += player.speed * ya;
// }

struct Vec2
{
    float x, y;
    
    void Add(const Vec2& other)
    {
        x += other.x;
        y += other.y; 
    }
};

// 结构体和类 本质上没有任何区别


int main()
{
    Player player;
    player.x = 5;
    
    player.y = 2;
    player.speed = 1;
    player.Move(1, -1);
    // Move(player, 1, -1);
    LOG(player.x);
    LOG(player.y);

    std::cin.get();
}

// 类本质上也只是语法糖，让我们的生活更容易
