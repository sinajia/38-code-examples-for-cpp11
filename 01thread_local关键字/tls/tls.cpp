// tls.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <thread>
#include <Windows.h>

using namespace std;

// 线程内部的全局变量

DWORD slot_ = TlsAlloc();

//int i = 0;
thread_local int i = 0;

class A {
public:
    thread_local static int i;
};

thread_local int A::i = 0;

void func() {
    for (;;) {
        int i = (int)TlsGetValue(slot_);
        TlsSetValue(slot_, (LPVOID)++i);
        cout << i << endl;
        if (i > 10)
            break;
    }
}

void func1() {
    for (;;) {
        ++A::i;
        cout << "func1 " << A::i << endl;
        if (A::i > 10)
            break;
    }
}

void func2() {
    for (;;) {
        ++A::i;
        cout << "func2 " << A::i << endl;
        if (A::i > 10)
            break;
    }
}

void func3() {
    thread_local int i = 1; //  编译器按照static处理
    for (;;) {
        cout << ++i << endl;
        if (i > 10)
            break;
    }
}

int main()
{
    {
        thread t1(func);
        this_thread::sleep_for(500ms);
        thread t2(func);

        t1.join();
        t2.join();
    }


    {
        //thread t1(func3);
        //this_thread::sleep_for(500ms);
        //thread t2(func3);

        //t1.join();
        //t2.join();
    }

}
