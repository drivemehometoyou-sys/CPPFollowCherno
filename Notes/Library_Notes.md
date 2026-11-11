# Cherno C++ 第 49--51 节：库的使用、链接与多项目组织

> 本笔记整理近期围绕三节课的讨论，并结合实际实验环境：Windows +
> w64devkit / MinGW-w64（GCC）+ VSCode。Cherno 使用的 Visual Studio /
> MSVC 与当前工具链有差异，文中会特别标出。

## 0. 总体认识：库解决什么问题？

假设有两个项目：

-   **Engine**：提供可复用功能，例如 `PrintMessage()`。
-   **Game**：调用 Engine 提供的功能。

如果每次构建 Game 都把 Engine
的所有源文件一起编译，项目变大后会出现重复编译、模块耦合和管理困难。可以先把
Engine 编译成库，再让 Game 使用。

理解库要区分三个层次：

1.  **头文件**：提供类型、函数等接口声明。
2.  **库文件**：提供接口背后的实现，或提供定位 DLL 实现所需的导入信息。
3.  **链接**：把程序需要的实现与应用程序建立联系。

例如：

``` cpp
// Engine.h
#pragma once
namespace engine
{
    void PrintMessage(); // 声明
}
```

``` cpp
// Engine.cpp
#include "Engine.h"
#include <iostream>

namespace engine
{
    void PrintMessage() // 定义：函数的实际实现
    {
        std::cout << "Hello,World!" << std::endl;
    }
}
```

``` cpp
// Application.cpp
#include "Engine.h"

int main()
{
    engine::PrintMessage();
}
```

`#include "Engine.h"`
让当前源文件看到声明，但**仅仅包含头文件，并不会自动把函数实现链接进程序**。

------------------------------------------------------------------------

# 第一部分：第 49 节------使用静态库（Static Linking）

## 1. 静态库是什么？

静态库通常是一个由一个或多个目标文件组成的**归档包**。在当前 MinGW-w64
环境中，常见扩展名是 `.a`；MSVC / Visual Studio 常见扩展名是 `.lib`。

静态链接时，链接器会从静态库中提取满足程序未解析符号所需的目标文件成员，并将所需代码链接进最终可执行文件。因此，程序运行时通常不再需要原来的静态库文件。

注意：`.lib` 也可能是 DLL 的导入库，不能只凭扩展名判断性质。

## 2. 静态库制作的三个阶段

Lesson41 的目录结构：

``` text
Lesson41/
├── Engine/
│   └── src/
│       ├── Engine.h
│       └── Engine.cpp
├── Game/
│   └── src/
│       └── Application.cpp
└── build/
```

### 阶段一：编译 Engine.cpp，生成目标文件

``` powershell
g++ -c Engine/src/Engine.cpp `
    -I"Engine/src" `
    -o build/Engine.o
```

  参数                  含义
  --------------------- ---------------------------
  `g++`                 GCC 的 C++ 编译器驱动程序
  `-c`                  只编译，不进行最终链接
  `-I"Engine/src"`      添加头文件搜索目录
  `-o build/Engine.o`   指定输出目标文件

`.o` 是 **Object File（目标文件）**：它已经不是普通 C++
源代码，但还没有完成最终链接。

### 阶段二：用 ar 将目标文件归档为静态库

``` powershell
ar rcs build/libEngine.a build/Engine.o
```

  参数   含义
  ------ ------------------------------------
  `ar`   GNU 归档工具
  `r`    将文件加入归档；同名成员存在时替换
  `c`    归档不存在时创建归档
  `s`    创建符号索引，便于链接器查找符号

检查库中包含哪些成员：

``` powershell
ar t build/libEngine.a
```

预期输出：

``` text
Engine.o
```

### 阶段三：Game 链接静态库

``` powershell
g++ Game/src/Application.cpp `
    -I"Engine/src" `
    build/libEngine.a `
    -o build/Game.exe
```

-   `-I"Engine/src"`：让编译器找到 `Engine.h`。
-   `build/libEngine.a`：把静态库交给链接器，提供 `PrintMessage()`
    的实现。

运行：

``` powershell
.\build\Game.exe
```

预期输出：

``` text
Hello,World!
```

流程图：

``` text
Engine.cpp
    | g++ -c
    v
Engine.o
    | ar rcs
    v
libEngine.a
    | 与 Application.cpp 一起链接
    v
Game.exe
```

## 3. 静态链接验证实验

可以把 `libEngine.a` 临时改名：

``` powershell
Rename-Item .\build\libEngine.a libEngine.a.bak
```

再运行：

``` powershell
.\build\Game.exe
```

如果程序仍正常运行，说明最终可执行文件已经包含运行所需的 Engine
实现，不再需要原来的静态库文件。

恢复：

``` powershell
Rename-Item .\build\libEngine.a.bak libEngine.a
```

注意：这不意味着静态库的所有内容都一定会无条件复制进
EXE。链接器通常只提取解决未解析符号所需的归档成员，具体还受链接选项影响。

------------------------------------------------------------------------

# 第二部分：第 50 节------使用动态库（Dynamic Library）

## 4. 动态库是什么？

Windows 下常见的动态链接库是 **DLL（Dynamic-Link Library）**。

与静态链接不同，动态链接不会把 DLL
中的函数实现作为普通静态库代码直接并入 EXE。程序运行时会依赖 DLL，由
Windows 加载器装载所需模块。

动态库的优势：

-   多个程序可以共享同一份 DLL。
-   在接口和兼容性满足要求时，可以替换 DLL
    实现，而不必重新链接每一个使用它的程序。

代价是：程序运行时必须能找到所需 DLL，且 DLL
的架构、接口和依赖项必须兼容。

## 5. Cherno 提到的两种动态库使用方式

### 方式 A：隐式动态链接（Implicit Linking / Load-time Dynamic Linking）

本次先实践这种方式。

特点：

-   编译时就知道要使用哪个 DLL。
-   编译时知道要调用 DLL 中哪些函数。
-   链接阶段使用**导入库（Import Library）**。
-   程序启动时由 Windows 加载器根据 EXE 的导入表加载 DLL。
-   源码中仍可直接调用函数，不需要自己写 `LoadLibrary()` 和
    `GetProcAddress()`。

### 方式 B：显式动态加载（Explicit Run-time Dynamic Linking）

程序运行时主动加载 DLL，并查找函数地址。Windows 常见 API：

-   `LoadLibrary()`：加载 DLL。
-   `GetProcAddress()`：根据导出名称获取函数地址。
-   `FreeLibrary()`：释放 DLL 模块。

示意：

``` cpp
HMODULE module = LoadLibraryA("Engine.dll");

if (module)
{
    using PrintMessageFn = void (*)();

    auto printMessage =
        reinterpret_cast<PrintMessageFn>(
            GetProcAddress(module, "SomeExportedFunction")
        );

    if (printMessage)
        printMessage();

    FreeLibrary(module);
}
```

这只是机制示意。真实项目还需处理导出名称、调用约定、函数签名、错误处理和模块生命周期。显式加载允许程序在运行时决定加载哪个
DLL；但调用函数时仍必须知道函数名称或约定，以及正确的函数签名。

**本次 Lesson41 实验采用方式 A：隐式动态链接。**

## 6. 为什么动态库会出现 DLL 和导入库两个文件？

MinGW-w64 下，本次实验会生成：

``` text
Engine.dll
libEngine.dll.a
```

它们不是同一个东西：

  文件                作用
  ------------------- -------------------------------------------------
  `Engine.dll`        真正的动态库，包含函数实现
  `libEngine.dll.a`   导入库，帮助链接器在构建阶段解析 DLL 导出的符号

导入库扩展名也是 `.a`，但它**不是包含 Engine
完整实现的普通静态库**。它主要提供导入信息和链接所需的辅助内容。

类比 GLFW：

``` text
glfw3.dll          # 真正的 DLL
libglfw3dll.a      # MinGW 使用的导入库
```

所以：

-   `libEngine.a`：静态库。
-   `Engine.dll`：动态库本体。
-   `libEngine.dll.a`：DLL 的导入库。

不能仅凭 `.a` 扩展名判断它一定是普通静态库。

## 7. 为什么需要 ENGINE_API 宏？

Windows DLL 通常要区分 DLL
的构建者和使用者：构建者导出函数，使用者导入函数。

在 `Engine.h` 中：

``` cpp
#pragma once

#ifdef ENGINE_BUILD_DLL
    #define ENGINE_API __declspec(dllexport)
#elif defined(ENGINE_USE_DLL)
    #define ENGINE_API __declspec(dllimport)
#else
    #define ENGINE_API
#endif

namespace engine
{
    ENGINE_API void PrintMessage();
}
```

  ----------------------------------------------------------------------------------
  场景              宏定义               展开结果                  含义
  ----------------- -------------------- ------------------------- -----------------
  编译 Engine DLL   `ENGINE_BUILD_DLL`   `__declspec(dllexport)`   导出函数

  编译使用者 Game   `ENGINE_USE_DLL`     `__declspec(dllimport)`   从 DLL 导入函数

  静态库版本        两者都不定义         空                        不使用 DLL
                                                                   导入/导出标记
  ----------------------------------------------------------------------------------

-   `__declspec(dllexport)`：告诉编译器当前 DLL 要向外部导出这个函数。
-   `__declspec(dllimport)`：告诉编译器这个函数由外部 DLL 提供。
-   GCC 的 `-DENGINE_BUILD_DLL` 相当于在预处理阶段定义
    `ENGINE_BUILD_DLL`；`-DENGINE_USE_DLL` 同理。它们不是运行时设置。

## 8. 动态库制作流程（MinGW-w64）

以下命令在 `Lesson41` 目录下执行。先确保 `build` 存在：

``` powershell
New-Item -ItemType Directory -Force build
```

### 阶段一：编译 Engine.cpp

``` powershell
g++ -c Engine/src/Engine.cpp `
    -I"Engine/src" `
    -DENGINE_BUILD_DLL `
    -o build/Engine.o
```

### 阶段二：生成 DLL 和导入库

``` powershell
g++ -shared build/Engine.o `
    -o build/Engine.dll `
    -Wl,--out-implib,build/libEngine.dll.a
```

  参数                    含义
  ----------------------- ------------------------------
  `-shared`               生成共享库 / DLL
  `build/Engine.o`        输入目标文件
  `-o build/Engine.dll`   指定 DLL 输出路径
  `-Wl,`                  将后面的选项传递给底层链接器
  `--out-implib,...`      要求链接器生成导入库

成功后：

``` text
build/
├── Engine.o
├── Engine.dll
└── libEngine.dll.a
```

### 阶段三：编译 Game 并链接导入库

``` powershell
g++ Game/src/Application.cpp `
    -I"Engine/src" `
    -DENGINE_USE_DLL `
    build/libEngine.dll.a `
    -o build/Game.exe
```

这里链接的是 `libEngine.dll.a`，不是 `Engine.dll`：

-   导入库负责构建阶段的链接。
-   DLL 负责程序运行时提供函数实现。

### 阶段四：运行程序

让 `Engine.dll` 与 `Game.exe` 位于同一个目录：

``` text
build/
├── Engine.dll
├── libEngine.dll.a
└── Game.exe
```

运行：

``` powershell
.\build\Game.exe
```

Windows 通常可以从应用程序所在目录找到所依赖的 DLL。

## 9. 验证 Game.exe 是否依赖 Engine.dll

使用 `objdump`：

``` powershell
objdump -p build/Game.exe | findstr /i /c:"DLL Name:"
```

预期类似：

``` text
DLL Name: KERNEL32.dll
DLL Name: msvcrt.dll
DLL Name: Engine.dll
```

-   `KERNEL32.dll`：Windows 系统 DLL。
-   `msvcrt.dll`：C 运行时相关 DLL。
-   `Engine.dll`：自己制作的 DLL。

如果出现 `Engine.dll`，说明 EXE 的导入信息记录了对它的依赖。

还可以把 `Engine.dll` 临时改名，再运行 `Game.exe`。Windows
应该提示无法找到 DLL。恢复文件名后程序应能再次运行。

## 10. 静态链接与动态链接对照

  对比维度                       静态链接                 隐式动态链接
  ------------------------------ ------------------------ --------------------------
  主要库文件                     `libEngine.a`            `Engine.dll`
  链接时使用                     静态库本身               导入库 `libEngine.dll.a`
  最终 EXE                       包含所需静态库目标代码   记录 DLL 依赖
  运行时是否需要 Engine 库文件   通常不需要               需要 DLL
  运行时加载                     不需要加载 Engine DLL    Windows 加载器加载 DLL
  更新库实现                     通常需要重新链接 EXE     接口兼容时可替换 DLL

------------------------------------------------------------------------

# 第三部分：第 51 节------创建与使用库（Visual Studio 多项目）

## 11. Cherno 为什么创建 Engine 和 Game 两个项目？

Cherno 在 Visual Studio 的一个 Solution（解决方案）中创建两个
Project（项目）：

``` text
Solution 'Game'
│
├── Engine
│   └── src/
│       ├── Engine.h
│       └── Engine.cpp
│
└── Game
    └── src/
        └── Application.cpp
```

-   Engine 负责提供可复用功能。
-   Game 负责调用 Engine。
-   两个项目独立组织，但通过项目依赖关系连接。

### Solution 与 Project

-   **Solution（解决方案）**：管理一组相关项目。
-   **Project（项目）**：描述一个具体构建目标，例如静态库、动态库或可执行程序。

一个 Solution 可以包含多个 Project。

## 12. 为什么 Cherno 把 Engine 的属性设置成 lib？

因为他希望 Engine 被编译成静态库，而不是直接生成 EXE。

在 Visual Studio / MSVC 中，Engine 项目的配置类型可以设置为：

``` text
Configuration Properties
    → General
        → Configuration Type
            → Static library (.lib)
```

Game 项目则设置为：

``` text
Application (.exe)
```

构建关系：

``` text
Engine 项目
    ↓
Engine.lib

Game 项目
    ↓
Game.exe
```

注意：Visual Studio 的 `.lib` 既可能是静态库，也可能是 DLL
导入库。需要结合项目配置类型和生成过程判断。

## 13. Project Reference（项目引用）有什么用？

Game 需要使用 Engine，可以给 Game 添加 Engine 的 Project Reference。

它主要解决：

1.  告诉构建系统：Game 依赖 Engine。
2.  建立项目构建顺序：通常先构建 Engine，再构建 Game。
3.  对静态库项目引用，配置相应链接依赖，使 Game 能链接 Engine 生成的
    `.lib`。

但**项目引用与头文件搜索路径不是同一个概念**。如果 Game 写：

``` cpp
#include "Engine.h"
```

编译器仍然必须知道 `Engine.h` 所在目录。通常需要配置：

``` text
C/C++
  → General
    → Additional Include Directories
```

或者使用公共属性表等方式统一管理头文件路径。

## 14. 为什么不继续写很长的相对路径？

例如：

``` cpp
#include "../../Engine/src/Engine.h"
```

小实验中可以工作，但目录结构变化后容易失效。更好的方式是：

``` cpp
#include "Engine.h"
```

然后通过头文件搜索路径告诉编译器去哪里找：

-   GCC / MinGW：`-I"Engine/src"`。
-   Visual Studio：`Additional Include Directories`。
-   VSCode IntelliSense：`c_cpp_properties.json` 中的 `includePath`。

这样源代码不必绑定某个具体目录层级。

## 15. Visual Studio 与当前 GCC + VSCode 环境的区别

Cherno 使用 Visual Studio / MSVC；当前环境是 VSCode + MinGW-w64 /
GCC。两者可以实现类似的工程组织，但配置机制和二进制格式并不完全相同。

  功能             Visual Studio / MSVC             当前环境：GCC + VSCode
  ---------------- -------------------------------- -----------------------------
  编译器           MSVC `cl.exe`                    MinGW `g++`
  静态库生成       MSVC Librarian                   GNU `ar`
  静态库常见格式   `.lib`                           `.a`
  动态库           `.dll`                           `.dll`
  DLL 导入库       `.lib`                           `.dll.a`
  项目组织         Solution / Project               文件夹与构建配置
  构建设置         项目属性                         命令行、`tasks.json`、CMake
  头文件搜索路径   Additional Include Directories   `-I`
  预处理宏         Preprocessor Definitions         `-D`

**不要默认 MSVC 生成的 `.lib` 能直接交给 MinGW 链接，或反过来。**
两套工具链的库格式、ABI
和运行时约定可能不同。使用预编译二进制库时必须确认兼容性。

------------------------------------------------------------------------

# 第四部分：结合自己的环境------VSCode、tasks.json 与头文件路径

## 16. `#include` 和 `-I` 分别负责什么？

``` cpp
#include "Engine.h"
```

表达的是当前源文件需要包含 `Engine.h`。编译器还必须知道去哪里找它。

GCC 可以通过：

``` powershell
-I"Engine/src"
```

添加搜索目录。

  内容                    作用
  ----------------------- ---------------------------
  `#include "Engine.h"`   指定要包含的头文件
  `-I"Engine/src"`        告诉 GCC 到哪里寻找头文件

## 17. `c_cpp_properties.json` 不等于编译命令

VSCode 的 Microsoft C/C++ 插件提供
IntelliSense，例如代码补全、错误提示、Ctrl + 点击跳转和头文件解析。

示意配置：

``` json
{
    "configurations": [
        {
            "name": "Win32",
            "includePath": [
                "${workspaceFolder}/**",
                "${workspaceFolder}/Lesson41/Engine/src"
            ],
            "compilerPath": "C:\\dev\\w64devkit\\bin\\g++.exe",
            "cppStandard": "gnu++20",
            "intelliSenseMode": "windows-gcc-x64"
        }
    ],
    "version": 4
}
```

它主要告诉 IntelliSense 如何理解代码，**不会自动替代真正的 GCC
编译命令**。实际编译仍需要 `-I`、`-D` 和库文件等参数。

## 18. `tasks.json` 是什么？

`tasks.json` 是 VSCode
的任务配置文件。它不是编译器，也不是完整构建系统，而是负责组织并调用外部工具，例如
`g++`、`ar` 和 `cmake`。

之前把三个静态库阶段串起来：

``` text
VSCode
   |
   v
tasks.json
   |
   ├── 调用 g++：编译 Engine.cpp
   ├── 调用 ar：制作 libEngine.a
   └── 调用 g++：链接 Game.exe
```

关键字段：

  字段               含义
  ------------------ ----------------------------
  `label`            任务名称
  `type`             任务执行类型
  `command`          要调用的程序
  `args`             传给程序的参数
  `options.cwd`      命令执行时的工作目录
  `dependsOn`        依赖的其他任务
  `dependsOrder`     依赖任务的执行顺序
  `problemMatcher`   解析编译器错误、警告等输出

示例：

``` json
{
    "label": "Compile Engine",
    "type": "process",
    "command": "g++",
    "args": [
        "-c",
        "Engine/src/Engine.cpp",
        "-I",
        "Engine/src",
        "-o",
        "build/Engine.o"
    ],
    "options": {
        "cwd": "${workspaceFolder}/Lesson41"
    },
    "problemMatcher": [
        "$gcc"
    ]
}
```

`command` 与 `args` 组合起来，相当于执行：

``` powershell
g++ -c Engine/src/Engine.cpp -I Engine/src -o build/Engine.o
```

之前使用：

``` json
"dependsOrder": "sequence"
```

让 VSCode 按顺序执行任务，避免 Engine.o 尚未生成就开始制作静态库。

按 `Ctrl + Shift + B` 可以触发默认构建任务。

## 19. tasks.json 与 CMake 的关系

### tasks.json

需要自己明确写出调用哪个程序、编译哪些文件、使用哪些路径和库，以及执行顺序。

### CMake

主要描述有哪些构建目标、每个目标由哪些源文件组成、目标之间有什么依赖，以及目标需要哪些头文件目录和库。

例如：

``` cmake
cmake_minimum_required(VERSION 3.20)

project(Lesson41 LANGUAGES CXX)

add_library(Engine STATIC
    Engine/src/Engine.cpp
)

target_include_directories(Engine PUBLIC
    Engine/src
)

add_executable(Game
    Game/src/Application.cpp
)

target_link_libraries(Game PRIVATE Engine)
```

这段 CMake 描述了：

1.  创建名为 Engine 的静态库目标。
2.  Engine 由 `Engine.cpp` 构建。
3.  Engine 对外提供 `Engine/src` 头文件目录。
4.  创建 Game 可执行程序。
5.  Game 链接 Engine。

CMake 再根据所选生成器和工具链生成具体构建规则。

------------------------------------------------------------------------

# 第五部分：核心知识总复习

## 20. 三节课的知识地图

``` text
C++ 库的使用与创建
│
├── 1. 静态库
│   ├── .cpp 编译为 .o
│   ├── ar 将 .o 归档为 .a
│   ├── 链接器从静态库提取所需目标代码
│   └── 最终生成 EXE
│
├── 2. 动态库
│   ├── DLL：真正的动态库
│   ├── 导入库：帮助链接器解析 DLL 符号
│   ├── dllexport：导出
│   ├── dllimport：导入
│   ├── 隐式动态链接
│   └── 显式动态加载
│
└── 3. 多项目组织
    ├── Solution 管理多个 Project
    ├── Engine 提供库
    ├── Game 使用库
    ├── Project Reference 管理项目依赖
    ├── Include Path 管理头文件搜索
    └── tasks.json / CMake 管理构建流程
```

## 21. 最容易混淆的概念

  --------------------------------------------------------------------------------------------
  容易混淆的概念                      正确区分
  ----------------------------------- --------------------------------------------------------
  头文件与库文件                      头文件提供声明；库文件提供实现或导入信息

  编译与链接                          编译源文件生成目标文件；链接解决符号引用并生成最终产物

  `.a` 与 `.dll.a`                    前者通常是静态库；后者通常是 DLL 导入库

  DLL 与导入库                        DLL 提供运行时实现；导入库用于链接阶段

  `dllexport` 与 `dllimport`          一个用于导出，一个用于导入

  `#include` 与 `-I`                  一个指定头文件；一个指定搜索目录

  `c_cpp_properties.json` 与          前者主要配置 IntelliSense；后者组织实际命令
  `tasks.json`                        

  tasks.json 与 CMake                 前者组织具体任务；后者描述目标和依赖并生成构建规则

  Solution 与 Project                 一个解决方案可以管理多个项目
  --------------------------------------------------------------------------------------------

## 22. 当前实验进度记录

### 已经实际完成

-   [x] 创建 Engine 与 Game 两个模块。
-   [x] 使用 `#include "Engine.h"` 和 `-I` 配置头文件搜索路径。
-   [x] 使用 `g++ -c` 生成 `Engine.o`。
-   [x] 使用 `ar rcs` 生成 `libEngine.a`。
-   [x] 使用 `ar t` 检查静态库内容。
-   [x] 链接静态库，生成 `Game.exe`。
-   [x] 成功运行程序，终端输出 `Hello,World!`。

### 已经学习并给出操作方案，仍待实际验证

-   [ ] 使用 `__declspec(dllexport)` / `__declspec(dllimport)`。
-   [ ] 使用 `g++ -shared` 生成 `Engine.dll`。
-   [ ] 生成 `libEngine.dll.a` 导入库。
-   [ ] 链接导入库并运行依赖 DLL 的 `Game.exe`。
-   [ ] 使用 `objdump` 检查 EXE 的 DLL 导入表。
-   [ ] 将动态库构建流程配置进 `tasks.json`。
-   [ ] 使用 CMake 管理 Engine 与 Game 两个构建目标。

## 23. 建议的后续学习顺序

1.  **先完成动态库实验**：亲自生成 DLL、导入库，并用 `objdump`
    检查依赖。
2.  **把静态库和动态库都写进
    tasks.json**：理解任务依赖、构建顺序和不同构建命令。
3.  **学习 CMake**：用
    `add_library()`、`add_executable()`、`target_link_libraries()`
    管理项目。
4.  **回头理解 Visual Studio 多项目机制**：把
    Solution、Project、项目引用、项目属性与 GCC / CMake 的概念对应起来。

最终要建立的认识是：

**C++ 工程开发不只是编写 `.cpp`
文件，还需要管理接口、实现、编译产物、库依赖、链接方式和构建流程。**
