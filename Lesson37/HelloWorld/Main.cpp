#include <iostream>
#include <vector>


struct Vertex
{
    float x, y, z;
};

std::ostream& operator<<(std::ostream& stream, Vertex& vertex)
{
    std::cout << vertex.x << ", " << vertex.y << ", " << vertex.z;
    return stream;  
}

std::ostream& operator<<(std::ostream& stream, const Vertex& vertex)
{
    std::cout << vertex.x << ", " << vertex.y << ", " << vertex.z;
    return stream;  
}

void Function(const std::vector<Vertex>& vertices)  // 一定要有引用，避免复制 const看情况
{
}

int main()
{
    // Vertex vertices[5];
    // Vertex* vertices = new Vertex[5];

    std::vector<Vertex> vertices; 
    vertices.push_back({1, 2, 3});  // 聚合初始化
    vertices.push_back({4, 5, 6});  
    
    Function(vertices);

    for(int i = 0; i < vertices.size(); i++)
        std::cout << vertices[i] << std::endl;  // []操作符重载
    
    // for(Vertex v : vertices) // 会发生复制，效率低             
    //     std::cout << v << std::endl;  
    for(Vertex& v : vertices)
        std::cout << v << std::endl;  
    
    vertices.erase(vertices.begin() + 1);

    for(const Vertex& v : vertices)
        std::cout << v << std::endl;  

    vertices.erase(vertices.begin() + 1);
    vertices.clear();

    std::cin.get();
}
