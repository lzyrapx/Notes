main函数执行之前，主要就是初始化系统相关资源：
1.设置栈指针
2.初始化static静态和global全局变量，即data段的内容
3.将未初始化部分的赋初值：数值型short，int，long等为0，bool为FALSE，指针为NULL，等等，即.bss段的内容
4.运行全局构造器，估计是C++中构造函数之类的吧
5.将main函数的参数，argc，argv等传递给main函数，然后才真正运行main函数

main 函数之后会执行相反的工作。
