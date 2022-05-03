// 23可执行对象封装器.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <functional>

using namespace std;

class A {
public:
    A() = default;
    A(int i) : m_i(i) {
        std::cout << "A(int i)" << std::endl;
    }
    void func(double d) {
        std::cout << d - m_i << std::endl;
    }
    ~A() {
        std::cout << "~A()" << std::endl;
    }
private:
    int m_i;
};

int func(int i) {
    cout << i << endl;
    return i;
}

std::function<void(double)> obtain() {
    return std::bind(&A::func, std::make_shared<A>(100), std::placeholders::_1);
}
int main() {
    {
        auto func = obtain();
        func(100.5);
    }

    {
        std::function<int()> funcc = std::bind(&func, 101);
        int r = funcc();
        cout << r << endl;
    }

    {
        std::function<void(int)> funcc = std::bind(&func, std::placeholders::_1);
        funcc(101);
    }


    return 0;

}
