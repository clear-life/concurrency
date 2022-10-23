#include<iostream>

using namespace std;

class A {
public:
    A() 
    {  
        cout << "构造" << endl;   // 1
    }
    ~A() 
    { 
        cout << "析构" << endl;   // 4
    }
    void fun() {
        cout << "do something!" << endl; 
    }
};
int main(void)
{
    A a;
    try {
        //A a;
        throw(std::string("error!"));  
        a.fun();
    }
    catch (string s) {    
        cout << s << endl;  // 2   
    }
    catch (...) {          // 其他类型异常
        cout << "..." << endl;
    }

    cout << "return 0!" << endl;    // 3
    return 0;
}