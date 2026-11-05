#include <iostream>
#include <string>

struct Vector2
{
    float x, y;

    Vector2(float x, float y)
    : x(x), y(y) {}

    Vector2 Add(const Vector2& other) const
    {
        return Vector2(x + other.x, y + other.y);
    }

    Vector2 operator+(const Vector2& other) const
    {
        return Add(other);
    }

    Vector2 Multiply(const Vector2& other) const
    {
        return Vector2(x * other.x, y * other.y);
    }

    Vector2 operator*(const Vector2& other) const
    {
        return Multiply(other);
    }

    bool operator==(const Vector2& other) const
    {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Vector2& other) const
    {
        return !(*this == other);
        // return !operator==(other);
    }

    // 这样也成立， 但有些奇怪
    // Vector2 Add(const Vector2& other) const
    // {
    //     return *this + other;
    //     // return operator+(other);
    // }
    // Vector2 operator+(const Vector2& other) const
    // {
    //     return Vector2(x + other.x, y + other.y);
    // }
};   

std::ostream& operator<<(std::ostream& stream, const Vector2& other)   // 非成员函数式的重载 
{
    stream << other.x << "," << other.y;
    return stream;
}

int main()
{
    Vector2 position(4.0f, 4.0f);
    Vector2 speed(0.5f, 1.5f);
    Vector2 powerup(1.1f, 1.1f);
    
    // Vector2 result = position.Add(speed);
    Vector2 result1 = position.Add(speed.Multiply(powerup));
    Vector2 result2 = position + speed * powerup;
 
    std::cout << result2 << std::endl;

    if(result1 == result2)

    std::cin.get();
} 

//对于二元运算符，如果采用成员函数形式，那么左边的对象必须是这个成员函数所属的类的对象
//这就是为什么 std::cout << a 通常使用非成员函数实现的根本原因