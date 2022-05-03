// 25原子类型 内存模型.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <atomic>
#include <Windows.h>

using namespace std;

int main() {
    {
        // long、int、long long、short、char、wchar_t
        // 编译器保证原子类型在多线程间互斥的访问
        std::atomic<int> a;
        a = 0;
        a.store(0);
        a = 1;
        cout << a.load() << endl;
        cout << a << endl;
        std::cout << a.fetch_add(1) << std::endl;
        cout << a.load() << std::endl;
        // CAS(compare and set)
        int i = 1;
        bool b = a.compare_exchange_strong(i, 10);
        cout << "b=" << b << ",a=" << a.load() << endl;
        // 原子交换
        a.exchange(0);
        cout << "a=" << a << endl;

    }

    {
        int a = 0;
        int b = 0;
        _ReadWriteBarrier(); // 内存栅栏
        int c = 0;
    }

}
