// 26多线程 同步.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <thread>
#include <mutex>
#include <functional>

using namespace std;

int a_ = 0;
std::mutex mutex_;

void func(string id) {
    std::lock_guard<std::mutex> guard(mutex_);
    cout << "threadId = " << id;
    this_thread::sleep_for(100ms);
    cout << " " << ++a_ << endl;
}

class A {
public:
    A() = default;
    void func(int i) {
        cout << "A::func(" << i << ")" << endl;
    }
};

int main()
{
    {
        std::thread t1{ func, "1" };
        this_thread::yield();
        std::thread t2{ func, "2" };

        t1.join();
        t2.join();
    }

    {
        std::shared_ptr<A> ptr = std::make_shared<A>();
        auto funcobj = std::bind(&A::func, ptr, std::placeholders::_1);
        std::thread t{ funcobj, 101 };
        t.join();
    }


    return 0;

}
