// 09constexpr关键字.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <random>

using namespace std;

unsigned int func() {
    default_random_engine e;
    return e();
}

// 函数返回值是常量，编译期可决议出来
template<class T>
constexpr T clone(const T& t) {
    return t;
}

int main()
{
    const int i = 0;
    {
        constexpr int i = 0;
    }
    // 运行期间初始化后不能再赋值
    const unsigned int b = func();
    {
        // 无法编译
        // constexpr unsigned int b = func();
    }

    cout << b << endl;

    {
        constexpr int a = 100;
        cout << clone(a); cout <<" " << 100 << endl;
    }

    {
        random_device rd;
        default_random_engine e { rd() };
        // 尽可能编译过不报错，退化为
        /*
           template<class T>
           T clone(const T& t) {
                return t;
           }
        */
        cout << clone(e());
    }

}
