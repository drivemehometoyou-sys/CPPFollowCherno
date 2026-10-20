#include <iostream>
#include <array>

class Entity
{
public:
    // const int size = 5;
    // int example[size]; // 不可以这样，当你在栈中为数组申请内存时候，它必须是一个编译时就知道的常量（但CPP可以修正，以后说
    
    // static constexpr int exampleSize = 5;
    static const int exampleSize = 5; // 在类内部，会变成依赖具体对象的非静态成员，所以必须加static

    int example[exampleSize]; 

    std::array<int,5> another;

    // int example[5];
    // int* example = new int[5];


    Entity()
    {
        // int a[5];
        // int count = sizeof(a) / sizeof(int);  // 会得到5
        // int count = sizeof(example) / sizeof(int);  // 会得到2 example 是一个8字节地址 
        // 这个方法有危险， 最好自己维护数组的大小  
        // std::cout << count << std::endl;

        // for(int i = 0; i < 5; i++)
        //     example[i] = 4;

        for(int i = 0; i < exampleSize; i++)
            example[i] = 4;
        
        for(int i = 0; i < another.size(); i++)
            example[i] = 4;
    }

};


int main()
{
    // int example[5];
    // example[0] = 1;
    // example[4] = 2;
    // example[5] = 3;  // 越界

    // std::cout << example[4] << std::endl;
    // std::cout << example[5] << std::endl;

    // std::cout << example << std::endl;

    // for(int i = 0; i < 5; i++)
    //     example[i] = 4;
    
    // example[2] = 3;
    // int* ptr = example;
    // *(ptr + 2) = 5;
    // // *((int*)((char*)ptr + 8)) = 9;

    // int* another = new int[5];
    // for(int i = 0; i < 5; i++)
    //     another[i] = 4;
    
// 用new和栈的最大区别是 生存期，例如我想在函数内部创建一个数组并能返回数组，只能用new，除非传入数组地址
// 还有一件事：

    Entity e;

// 堆的时候：内存间接寻址我们实际得到的e的内存地址，看到e实际包含另一个地址，是我们数组的实际地址
// 意味着当我们想要访问数组时，实际上会在内存跳来跳去，所以最好在 栈 上创建数组    

// 而且： 在堆中创建的数组，我们无法知道它的占内存大小    
    std::cin.get();
} 
