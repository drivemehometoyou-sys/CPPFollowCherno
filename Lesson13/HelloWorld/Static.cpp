// static int s_Variable = 3;

// int s_Variable = 3;

static int s_Variable = 3;


static void Fuction()
{
    
}

// 声明静态函数或静态变量， 它只会在被声明的C++文件中被看到（当前翻译单元）

// 误区：文件作用域的 static 限制的是符号的链接属性，而不是禁止其他文件通过 #include 看到它的源代码。