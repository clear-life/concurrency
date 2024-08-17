#include <string>
#include <future>

struct X
{
    std::string fun(std::string const&);
};

X x;
auto f1 = std::async(&X::fun, &x, "hello");     // x.fun()
auto f2 = std::async(&X::fun, x, "goodbye");    // x 值传递生成副本 t, t.fun()


struct Y
{
    double operator()(double);
};

Y y;
auto f3 = std::async(Y(), 1.0);                   // Y() 默认构造生成匿名变量 t, t.operator()
auto f4 = std::async(std::ref(y), 1.0);           // 引用传递, y.operator()


X fun(X&);      // 函数 fun
auto f6 = std::async(fun,std::ref(x));      // fun()


class move_only // 只有移动操作的类
{
public:
    void operator()();
};
auto f5 = std::async(move_only());          // 默认构造生成副本, 然后移动构造在 std::sync() 内产生临时对象 t, t.operator()
