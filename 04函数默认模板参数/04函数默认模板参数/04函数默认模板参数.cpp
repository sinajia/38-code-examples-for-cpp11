// 04函数默认模板参数.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

using namespace std;

template<typename T, typename S = int>
S func(T t) {
    cout << t << endl;
    return sizeof(S);
}

int main() {
    cout << (func(5.5));
    return 0;
}
