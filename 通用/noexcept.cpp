/*
noexcept:
1. 修饰函数表示不抛出异常
2. 接收常量表达式, 根据结果表明会不会抛出异常
*/

void func() noexcept;               // 不抛出异常
void func() noexcept(常量表达式);    // 常量表达式为 true, 函数为 noexcept, 否则为 non-noexcept

template<>
void func() noexcept(noexcept(T()));
// noexcept(T()) 的结果由 T() 是否抛出异常决定, 不抛出为 true, 否则为 false
// func 是否为 noexcept 由 noexcept(T()) 决定
