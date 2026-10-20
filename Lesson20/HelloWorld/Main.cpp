#include <iostream>

class Entity 
{
// private:
// protected:
public:
    int X, Y;
    void Print() {};
public:
    Entity()
    {
        X = 0;
        Print();
    }
};


class Player : public Entity
{
private:

public:
    Player()
    {
        // X = 0;  // X是private, 不可行
        X = 0; // protected 后就可以了
        Print(); 
    }

};


int main()
{
    Entity e;
// private：
    // e.X = 0;  // 不可行， 只有Entity类和它的友元可以 
    // e.Print();  // same

// protected:
    // e.X = 0;  // 不可行， 只有Entity和它的子类可以 
    // e.Print();  // same
// public:
    e.X = 0; // 可以了   
    e.Print();  



    std::cin.get();
} 
