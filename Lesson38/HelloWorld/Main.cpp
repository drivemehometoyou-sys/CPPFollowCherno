#include <iostream>
#include <vector>


struct Vertex
{
    float x, y, z;

    Vertex(float x, float y, float z)
        :x(x), y(y), z(z)
    {
    }

    Vertex(const Vertex& Vertex)
        :x(Vertex.x), y(Vertex.y), z(Vertex.z)
    {
        std::cout << "Copied!" << std::endl;
    }
};


int main()
{
    std::vector<Vertex> vertices; 
    
    // vertices.reserve(3);    // 法1：要求 vector 至少预留能够容纳 3 个元素的存储空间。

    // vertices.push_back(Vertex(1, 2, 3));    // 1  
    // vertices.push_back(Vertex(4, 5, 6));    // 2
    // vertices.push_back(Vertex(4, 5, 6));    // 3

    vertices.reserve(3);    // 法2：要求 vector 至少预留能够容纳 3 个元素的存储空间。
    vertices.emplace_back(1, 2, 3);      // 直接在 vector 已经分配好的存储空间中构造对象，避免创建临时对象再拷贝进去。
    vertices.emplace_back(4, 5, 6);    // emplace_back() 将参数直接传递给元素的构造函数，在 vector 预留的存储空间中直接构造对象，无需创建临时对象再拷贝或移动。
    vertices.emplace_back(4, 5, 6);    
    
 

    std::cin.get();
}
