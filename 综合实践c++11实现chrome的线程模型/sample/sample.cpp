// sample.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
#include <conio.h>
#include "../base/thread.h"
#include "../base/time.h"

using namespace std;

class A {
public:
    void func1(int i, double d) {
        std::cout << "func1" << " i= " << i << " d=" << d << std::endl;
    }

    void func2() {
        std::cout << "func2 i_=" << i_++ << std::endl;
    }
    static int i_;
};

int A::i_ = 0;

int main()
{
    using namespace std::chrono_literals;

    base::Thread thread;
    thread.StartWithOptions(base::Thread::Options());

    std::shared_ptr<A> ptr = std::make_shared<A>();

    int i = 0;
    double d = 3.0;

    for (;;) {
        ++i;
        thread.message_loop()->PostTask(std::bind(&A::func1, ptr, i, ++d));
        thread.message_loop()->PostDelayedTask(std::bind(&A::func2, ptr), 10ms);

        if (i > 100) {
            break;
        }
    }

    while ((!_kbhit() || _getch() != 27)) {
        std::cout << static_cast<unsigned int>(base::TimeTicks::Now().ToInternalValue() / 1000) << std::endl;
        std::this_thread::sleep_for(2s);
    }

    thread.Stop();

    return 0;

}
