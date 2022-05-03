// 33变长模板参数.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <string>
#include <tuple>

using namespace std;

template<typename T>
void tfunc(T t) {
    cout << t << endl;
}

template<typename T, typename... Types>
void tfunc(T t, Types... args) {
    cout << t << endl;
    tfunc(args...);
}

template<typename... Types>
class A1 {
public:
    A1() {
        // 打印模板参数个数
        cout << sizeof...(Types) << endl;
    }
};

template<typename... Types> class Tuple;

template<typename T, typename... Types>
class Tuple<T, Types...> : public Tuple<Types...> {
public:
    Tuple(T t, Types... args) : Tuple<Types...>(args...) {
        t_ = t;
    }
    T t_;
    void output() {
        cout << t_ << endl;
        Tuple<Types...>::output();
    }
};

template<>
class Tuple <> {
public:
    void output() {}
};

int main()
{
     tfunc(1, 2, 3);

     A1<char, int, double, float> ta1;

     cout << endl;

    {
        std::tuple<double, int, std::string> tuple3 = std::make_tuple(0.1, 1, "hello");
        cout << std::get<0>(tuple3) << endl;
        cout << std::get<1>(tuple3) << endl;
        cout << std::get<2>(tuple3) << endl;
    }

    cout << endl;

    {
        Tuple<int, double, std::string> tple(1, 1.3, "hello");
        tple.output();
    }

    return 0;
}
