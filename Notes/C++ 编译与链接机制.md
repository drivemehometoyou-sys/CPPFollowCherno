# C++ 编译与链接机制

> 学习主题：预处理、编译、汇编、链接、头文件、extern、static、静态链接与动态链接  
> 开发环境：Windows + w64devkit + MinGW-w64 + GCC 16.1.0

---

# 一、C++ 程序从源代码到可执行文件

## 1. 整体流程

一个 C++ 项目通常由多个 `.cpp` 和 `.h` 文件组成。每个 `.cpp` 文件通常独立编译，最后通过链接器组合成一个可执行程序。

完整流程：

```text
             C++ 源代码
          Main.cpp  Math.cpp
                |
                v
          1. 预处理 Preprocessing
          展开 #include、宏替换等
                |
                v
          2. 编译 Compilation
          C++ 源代码转换为汇编代码
                |
                v
          3. 汇编 Assembly
          汇编代码转换为机器指令
                |
                v
          目标文件 Object File
             Main.o  Math.o
                |
                v
          4. 链接 Linking
          符号解析、重定位、组合目标文件
                |
                v
          最终可执行文件
             Main.exe
```

注意：预处理、编译、汇编、链接是不同的阶段。GCC/G++ 的驱动程序可以自动调用相应工具完成整个过程。

## 2. GCC 常用命令

假设有一个 `Main.cpp`：

| 命令 | 作用 | 输出 |
|---|---|---|
| `g++ -E Main.cpp -o Main.i` | 预处理 | `.i` |
| `g++ -S Main.cpp -o Main.s` | 生成汇编代码 | `.s` |
| `g++ -c Main.cpp -o Main.o` | 编译并汇编，不链接 | `.o` |
| `g++ Main.cpp -o Main.exe` | 完整构建 | `.exe` |

几个细节：

- `-E`：完成预处理后停止。
- `-S`：完成预处理、编译后停止，输出汇编代码。
- `-c`：完成预处理、编译、汇编后停止，不进行链接。
- 不使用这些停止选项时，通常会继续完成链接。

`.o` 是目标文件（Object File），其中包含机器代码、数据、符号信息和重定位信息等。

---

# 二、源代码组织：.h 和 .cpp

## 1. 为什么要区分头文件和源文件？

大型项目通常需要模块化。

例如：

```text
MyProject/
│
├── Main.cpp
├── Math.cpp
└── Math.h
```

通常：

- `.h` / `.hpp`：声明接口，让其他源文件知道有哪些功能。
- `.cpp`：实现具体功能。

例如：

Math.h：

```cpp
#pragma once

int Add(int a, int b);
```

这里声明了一个函数：

```cpp
int Add(int a, int b);
```

告诉编译器：

存在一个名为 Add 的函数，接收两个 int，返回一个 int。

但没有提供具体实现。

Math.cpp：

```cpp
#include "Math.h"

int Add(int a, int b)
{
    return a + b;
}
```

这里才是函数定义。

Main.cpp：

```cpp
#include <iostream>
#include "Math.h"

int main()
{
    std::cout << Add(2, 3) << std::endl;
}
```

Main.cpp 通过包含 Math.h，获得 Add 的声明，因此可以使用这个函数。

## 2. #include 到底是什么？

`#include` 是预处理指令。

它的本质是：

**将指定文件的内容引入当前源文件，参与预处理。**

例如：

```cpp
#include <iostream>
#include "Math.h"
```

预处理器会将相应头文件的内容引入当前翻译单元。

注意：

**#include 不等于编译另一个 cpp 文件，更不等于链接。**

例如：

```cpp
#include "Math.h"
```

不会自动把 `Math.cpp` 编译进来。

所以需要分别编译：

```bash
g++ -c Main.cpp -o Main.o
g++ -c Math.cpp -o Math.o
```

然后链接：

```bash
g++ Main.o Math.o -o Main.exe
```

## 3. #include 的两种常见形式

```cpp
#include <iostream>
#include "Math.h"
```

通常：

- `< >`：用于标准库头文件或配置的系统头文件搜索路径。
- `" "`：通常优先搜索当前文件所在目录，再搜索其他配置的目录。

具体搜索顺序还受到编译器选项和实现影响。

## 4. 为什么需要 #pragma once？

如果多个头文件间存在相互包含，或者同一个头文件被重复包含，可能导致重复声明甚至重复定义。

常见解决方案：

```cpp
#pragma once
```

或者传统的 Include Guard：

```cpp
#ifndef MATH_H
#define MATH_H

int Add(int a, int b);

#endif
```

它们的作用是防止同一个头文件在同一个翻译单元中被重复处理。

注意：Include Guard 不能代替 ODR，也不能自动解决多个 cpp 中重复定义函数的问题。

---

# 三、声明（Declaration）与定义（Definition）

这是理解多文件编程的基础。

## 1. 声明

声明告诉编译器：

某个变量、函数、类型等实体存在，并提供使用它所需的信息。

例如：

```cpp
int Add(int a, int b);
```

这是函数声明。

它告诉编译器：

- 函数名：Add
- 参数：两个 int
- 返回值：int

但是没有提供函数体。

## 2. 定义

定义提供实体本身，或者函数的具体实现。

```cpp
int Add(int a, int b)
{
    return a + b;
}
```

这是函数定义。

## 3. 对比

```cpp
// 声明
int Add(int a, int b);

// 定义
int Add(int a, int b)
{
    return a + b;
}
```

变量也是类似的：

```cpp
extern int g_Value;  // 变量声明

int g_Value = 100;   // 变量定义
```

注意：

`extern int g_Value = 100;` 虽然有 extern，但由于提供了初始化器，仍然是变量定义。

---

# 四、extern：跨文件引用

## 1. extern 的作用

`extern` 常用于声明具有外部链接属性的变量或函数，让其他翻译单元能够引用它们。

例如：

Main.cpp：

```cpp
#include <iostream>

extern int g_Value;

int main()
{
    std::cout << g_Value << std::endl;
}
```

Data.cpp：

```cpp
int g_Value = 100;
```

这里：

```cpp
extern int g_Value;
```

表示：

存在一个叫 g_Value 的外部变量，它的定义在其他地方。

而：

```cpp
int g_Value = 100;
```

提供了真正的变量定义。

链接器负责将它们对应起来。

## 2. 推荐使用头文件组织

Data.h：

```cpp
#pragma once

extern int g_Value;
```

Data.cpp：

```cpp
#include "Data.h"

int g_Value = 100;
```

Main.cpp：

```cpp
#include "Data.h"

int main()
{
    return g_Value;
}
```

这样，其他源文件只需要包含 Data.h 就可以使用这个变量。

## 3. 函数为什么经常不写 extern？

例如：

```cpp
int Add(int a, int b);
```

普通的命名空间作用域函数声明默认就具有外部链接。

所以通常不需要：

```cpp
extern int Add(int a, int b);
```

两者在通常情况下具有相同的外部链接含义。

## 4. extern 的核心认识

- 声明和定义是不同的。
- extern 常用于跨翻译单元引用外部实体。
- 它不会自动把其他 cpp 文件编译进来。
- 最终仍然需要链接器找到对应的定义。

---

# 五、static：存储期与链接属性

static 在 C++ 中有多种用途，必须结合它所在的位置理解。

## 1. 文件作用域的 static

例如：

```cpp
// Data.cpp

static int g_Value = 100;
```

这里的 static 使变量具有内部链接（Internal Linkage）。

意味着：

这个变量只能通过 Data.cpp 所属的翻译单元内部的名称访问，其他 cpp 文件不能通过外部链接引用它。

例如：

```cpp
// Main.cpp

extern int g_Value;

int main()
{
    return g_Value;
}
```

这时链接器无法找到对应的外部定义。

因为 Data.cpp 中的 g_Value 具有内部链接。

## 2. 函数内部的 static

```cpp
void Function()
{
    static int count = 0;

    count++;

    std::cout << count << std::endl;
}
```

调用：

```cpp
int main()
{
    Function();
    Function();
    Function();
}
```

输出：

```text
1
2
3
```

原因：

普通局部变量通常具有自动存储期，函数执行结束后生命周期结束。

但局部 static 变量具有静态存储期：

- 程序运行期间一直存在。
- 只初始化一次。
- 变量名仍然只在函数内部可见。

这里要区分：

**存储期（Storage Duration）不等于链接属性（Linkage）。**

## 3. 类中的 static

```cpp
class Entity
{
public:
    static int count;
};
```

这里的 count 是类级别的静态成员。

它不属于某个具体 Entity 对象，而是由整个类共享。

通常需要在类外定义：

```cpp
int Entity::count = 0;
```

C++17 之后也可以使用：

```cpp
class Entity
{
public:
    inline static int count = 0;
};
```

## 4. static 的几种含义总结

| 使用位置 | 主要作用 |
|---|---|
| 命名空间/文件作用域变量 | 内部链接 |
| 命名空间/文件作用域函数 | 内部链接 |
| 函数内部局部变量 | 静态存储期 |
| 类的静态成员变量 | 整个类共享一份 |
| 类的静态成员函数 | 不依赖具体对象调用 |

重点：

**文件作用域 static 与局部 static 不是一回事。**

前者重点是链接属性，后者重点是存储期。

---

# 六、链接器（Linker）到底在做什么？

## 1. 什么是符号（Symbol）？

目标文件 `.o` 中不仅有机器代码，还包含符号信息。

你可以暂时把符号理解为：

程序中需要被识别和引用的函数、变量等实体的名称。

例如：

```cpp
int Add(int a, int b)
{
    return a + b;
}
```

Add 就是一个函数符号。

## 2. 符号解析（Symbol Resolution）

假设：

Main.cpp：

```cpp
int Add(int a, int b);

int main()
{
    return Add(2, 3);
}
```

Math.cpp：

```cpp
int Add(int a, int b)
{
    return a + b;
}
```

分别编译：

```bash
g++ -c Main.cpp -o Main.o
g++ -c Math.cpp -o Math.o
```

此时：

- Main.o 中存在对 Add 的外部引用。
- Math.o 中存在 Add 的具体定义。

链接器负责找到对应的定义，解决符号引用。

## 3. 重定位（Relocation）

目标文件在生成时，部分代码和数据的最终地址还没有确定。

链接器需要根据最终布局，调整相关地址引用。

这个过程叫重定位。

例如：

```text
Main.o 中调用 Add()
       |
       | 原先地址尚未确定
       |
       v
链接器找到 Math.o 中的 Add()
       |
       v
修正调用位置和相关地址信息
```

这就是重定位的基本思想。

## 4. 链接器的主要工作

- 符号解析：寻找函数、变量的对应定义。
- 重定位：修正地址引用。
- 组合目标文件。
- 处理库依赖。
- 生成最终可执行文件或其他链接产物。

---

# 七、ODR：单一定义规则

ODR 全称：

One Definition Rule。

中文叫单一定义规则。

它是 C++ 程序组织中非常重要的规则。

一般来说，一个程序中的普通非 inline 外部链接函数或变量，只能有一个定义。

## 1. 一个典型错误

Math.h：

```cpp
int Add(int a, int b)
{
    return a + b;
}
```

Main.cpp：

```cpp
#include "Math.h"
```

Other.cpp：

```cpp
#include "Math.h"
```

由于 include 是文本引入，两个 cpp 都会获得一份 Add 函数定义。

编译之后：

```text
Main.o  → 定义 Add()
Other.o → 定义 Add()
```

链接时，可能出现：

```text
multiple definition of Add()
```

因为出现了不允许的重复定义。

## 2. 正确写法

Math.h：

```cpp
#pragma once

int Add(int a, int b);
```

Math.cpp：

```cpp
#include "Math.h"

int Add(int a, int b)
{
    return a + b;
}
```

其他 cpp 只包含头文件。

这样通常只有 Math.cpp 提供一个 Add 的定义。

## 3. inline 的特殊情况

C++ 允许符合 ODR 规则的 inline 函数定义出现在多个翻译单元中。

例如：

```cpp
// Math.h

#pragma once

inline int Add(int a, int b)
{
    return a + b;
}
```

每个包含 Math.h 的 cpp 都能看到定义。

符合 inline ODR 要求时，不会因为这种重复定义而违反 ODR。

C++17 还引入了 inline 变量。

注意：inline 不只是优化提示，它还涉及语言层面的链接和 ODR 规则。

---

# 八、静态链接与动态链接

这两个概念讨论的是程序如何使用外部库。

注意：

**静态链接与 static 关键字不是一回事。**

## 1. 静态链接（Static Linking）

静态库通常是已经编译好的目标文件集合。

常见格式：

- Windows / MinGW：`.a`、`.lib`
- Linux：`.a`

静态链接时，链接器从静态库中提取程序需要的目标代码，并将其纳入最终可执行文件。

```text
       Main.o
          |
          |
       libMath.a
          |
          v
        链接器
          |
          v
       Main.exe
```

特点：

- 最终可执行文件通常更大。
- 不需要运行时再查找对应的静态库文件。
- 更新库通常需要重新链接程序。
- 链接器通常只提取需要的目标文件或代码部分，而不是无差别复制整个库。

## 2. 动态链接（Dynamic Linking）

动态库是独立存在的库文件。

常见格式：

- Windows：`.dll`
- Linux：`.so`
- macOS：`.dylib`

动态链接时：

程序在构建阶段建立与动态库的依赖关系，运行时由操作系统加载器加载对应的库。

```text
       Main.exe
          |
          | 运行时依赖
          |
          v
        Math.dll
```

特点：

- 可执行文件通常较小。
- 多个程序可以共享同一份动态库。
- 在 ABI 兼容等条件满足时，可以独立更新动态库。
- 运行时必须能找到兼容的动态库，否则程序可能无法启动。

## 3. 静态链接与动态链接对比

| 对比 | 静态链接 | 动态链接 |
|---|---|---|
| 常见库格式 | `.a`、`.lib` | `.dll`、`.so` |
| 库代码 | 所需代码纳入程序 | 独立存在 |
| 可执行文件 | 通常较大 | 通常较小 |
| 运行时依赖 | 不依赖对应静态库文件 | 依赖动态库 |
| 多程序共享 | 通常不共享同一份代码映射 | 可以共享 |
| 更新库 | 通常重新链接 | 满足兼容条件时可独立更新 |

## 4. MinGW 的 DLL 导入库

在 Windows + MinGW 环境下，你可能看到：

```text
Math.dll
libMath.dll.a
```

两者不是同一个东西。

- `Math.dll`：真正的动态库，运行时需要。
- `libMath.dll.a`：导入库，帮助链接器在构建阶段解析 DLL 的导出接口。

这是 Windows 动态链接机制中的一个常见细节。

---

# 九、常见编译与链接错误

| 错误信息 | 常见原因 |
|---|---|
| `undefined reference` | 找不到函数或变量的定义 |
| `multiple definition` | 存在不允许的重复定义 |
| `undefined reference to WinMain` | Windows 子系统或入口点配置不匹配等 |
| `cannot find -lxxx` | 找不到指定的库 |
| `undefined reference to ...` | 也可能是库链接顺序、ABI 或符号名称不匹配 |

## 1. undefined reference

例如：

```cpp
// Main.cpp

int Add(int a, int b);

int main()
{
    return Add(2, 3);
}
```

如果只执行：

```bash
g++ Main.cpp -o Main.exe
```

没有把 Math.cpp 编译链接进来，就可能报：

```text
undefined reference to `Add(int, int)'
```

解决：

```bash
g++ Main.cpp Math.cpp -o Main.exe
```

## 2. multiple definition

常见原因：

在多个 cpp 中包含了具有普通外部链接的非 inline 函数定义。

解决思路：

- 头文件放声明。
- 源文件放定义。
- 必要时合理使用 inline。
- 检查是否违反 ODR。

---

# 十、完整的多文件项目实验

这是最值得亲自运行的一部分。

## 1. 项目结构

```text
MyProject/
│
├── Main.cpp
├── Math.h
└── Math.cpp
```

## 2. Math.h

```cpp
#pragma once

int Add(int a, int b);
```

## 3. Math.cpp

```cpp
#include "Math.h"

int Add(int a, int b)
{
    return a + b;
}
```

## 4. Main.cpp

```cpp
#include <iostream>
#include "Math.h"

int main()
{
    std::cout << Add(2, 3) << std::endl;

    std::cin.get();
}
```

## 5. 分别编译

```bash
g++ -c Main.cpp -o Main.o

g++ -c Math.cpp -o Math.o
```

此时目录中出现：

```text
Main.o
Math.o
```

## 6. 链接

```bash
g++ Main.o Math.o -o Main.exe
```

## 7. 运行

```bash
./Main.exe
```

输出：

```text
5
```

## 8. 一条命令完成

也可以直接：

```bash
g++ Main.cpp Math.cpp -o Main.exe
```

G++ 会自动完成整个构建流程。

---

# 十一、核心知识关系图

```text
                    C++ 项目
                       |
             +---------+---------+
             |                   |
          .h/.hpp              .cpp
             |                   |
        声明、接口            定义、实现
             |                   |
             +---------+---------+
                       |
                    #include
                       |
                 预处理阶段
                       |
                  翻译单元
                       |
                编译 + 汇编
                       |
                    .o 文件
                       |
               +-------+-------+
               |               |
           符号解析          重定位
               |               |
               +-------+-------+
                       |
                    链接器
                       |
              +--------+--------+
              |                 |
           静态链接           动态链接
              |                 |
         库代码纳入程序      运行时依赖动态库
              |                 |
              +--------+--------+
                       |
                  可执行程序
```

---

# 十二、最后复习：最重要的十个结论

1. `#include` 是预处理操作，不是编译或链接。
2. `.h` 通常放声明，`.cpp` 通常放定义。
3. 每个 `.cpp` 通常独立编译，形成一个翻译单元。
4. `.o` 是目标文件，包含机器代码、符号和重定位信息等。
5. `extern` 常用于跨翻译单元引用外部实体。
6. 文件作用域的 `static` 使变量或函数具有内部链接。
7. 函数内部的 `static` 主要体现静态存储期。
8. 链接器负责符号解析和重定位。
9. ODR 规定了程序中实体定义的相关约束。
10. 静态链接与动态链接是两种不同的库链接方式，与 `static` 关键字不是一回事。

---

# 十三、建议掌握程度

| 知识点 | 建议掌握程度 |
|---|---|
| 预处理、编译、汇编、链接 | 理解完整流程 |
| #include | 理解文本引入机制 |
| .h 和 .cpp | 能独立组织多文件项目 |
| 声明与定义 | 必须熟练区分 |
| extern | 能实现跨文件变量引用 |
| static | 理解不同作用域下的区别 |
| 符号与重定位 | 理解链接器的基本工作 |
| ODR | 能判断常见重复定义问题 |
| 静态链接、动态链接 | 理解原理与运行时区别 |
| GCC 构建命令 | 能独立完成多文件编译链接 |

**学习建议：**

不要只记概念。最有效的复习方式是亲自创建一个包含三个 `.cpp` 和两个 `.h` 的项目，分别尝试：

- 删除一个函数定义，观察 `undefined reference`。
- 在头文件中直接定义普通函数，观察 `multiple definition`。
- 给全局变量添加 `static`，观察跨文件引用的变化。
- 使用 `extern` 实现跨文件变量共享。
- 分别执行 `-E`、`-S`、`-c`，观察生成文件的区别。

能够解释这些实验的结果，就说明你真正理解了 C++ 的编译与链接机制。