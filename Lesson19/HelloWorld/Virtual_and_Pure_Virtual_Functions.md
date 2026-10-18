# C++ 虚函数与纯虚函数核心笔记（Cherno）

## ① 虚函数（Virtual Function）

关键词：运行时多态、动态绑定
```python
class Entity
{
public:
    virtual std::string GetName() { return "Entity"; }
};

class Player : public Entity
{
public:
    std::string GetName() override { return "Player"; }
};
```

- 目的：通过统一的基类接口，让不同派生类表现出各自的行为。
- `virtual`：通过基类指针或引用调用虚函数时，根据对象的动态类型选择最终重写版本。
- `override`：表示重写基类虚函数，非必需，但建议使用，可让编译器检查。
- 非虚函数：通常根据表达式的静态类型决定调用哪个版本。
```perl
Player p;
Entity* e = &p;   // 向上转型
e->GetName();     // 返回 "Player"
```

核心：继承实现类型统一，虚函数实现行为不同。

## ② 纯虚函数（Pure Virtual Function）

关键词：抽象类、接口、强制约定
```python
class Printable
{
public:
    virtual void Print() = 0;
    virtual ~Printable() = default;
};

class Player : public Printable
{
public:
    void Print() override
    {
        std::cout << "Player";
    }
};
```

- `= 0`：将虚函数声明为纯虚函数。
- 抽象类：具有未得到具体实现的纯虚函数，不能直接实例化。
- 派生类若想实例化，必须具有所有继承的纯虚函数的具体实现。
- 抽象类可以作为指针或引用类型，统一处理不同派生类对象。
- 目的：规定接口，让不同类遵循相同的功能约定。
```cpp
Printable* p = new Player(); // 合法
// Printable obj;            // 错误：抽象类不能实例化
p->Print();                   // 调用 Player::Print()
delete p;
```

## ③ 两者的区别

| 对比 | 虚函数 | 纯虚函数 |
| - | - | - |
| 声明 | `virtual void F() {}` | `virtual void F() = 0;` |
| 基类默认行为 | 通常提供 | 不要求提供 |
| 派生类是否必须重写 | 不必须 | 具体派生类必须有实现 |
| 基类能否实例化 | 可以（无其他纯虚函数时） | 不可以 |
| 核心目的 | 允许不同实现 | 规定统一接口 |

## ④ Cherno 的核心设计思想
```cpp
void PrintName(Entity* entity)
{
    std::cout << entity->GetName();
}
```

调用者依赖基类接口，不依赖具体派生类。

- 向上转型：`Player*` 可以转换为 `Entity*`。
- 动态多态：通过 `Entity*` 调用虚函数，执行实际对象对应的实现。
- 纯虚函数：进一步规定具体派生类必须满足的接口要求。

虚函数的常见实现机制：虚表（vtable）和虚表指针（vptr）。虚函数调用通常通过固定表项间接调用，而不是遍历整张虚表。

### 最终记忆

虚函数：统一接口，不同行为。

纯虚函数：只规定接口，要求具体类提供实现。

一句话总结：继承建立类型关系，虚函数实现运行时多态，纯虚函数定义接口约定。
