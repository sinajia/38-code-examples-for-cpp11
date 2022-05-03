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
        cout << "测试compare_exchange" << endl;
        {
            int i = 2;
            cout << "a=" << a << "，i=" << i << endl;
            bool r = a.compare_exchange_strong(i, 10); // 原子地比较原子对象与非原子参数的值，若相等则进行交换，若不相等则进行加载
            cout << "a.compare_exchange_strong(i, 10)的返回值是" << r << "，a = " << a << "，i = " << i << endl;
        }
        {
            a = 2;
            int i = 1;
            cout << "a=" << a << "，i=" << i << endl;
            bool r = a.compare_exchange_strong(i, 10);
            cout << "a.compare_exchange_strong(i, 10)的返回值是" << r << "，a = " << a << "，i = " << i << endl;
        }
        // 原子交换
        {
            cout << "测试原子交换exchange" << endl;
            cout << "a=" << a << endl;
            cout << "a.exchange(100)的返回值是" << a.exchange(100) << endl;
            cout << "a=" << a << endl;
        }

    }

    {
        int a = 0;
        int b = 0;
        _ReadWriteBarrier(); // 内存栅栏
        int c = 0;
    }

}
