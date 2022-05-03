// 26多线程 同步.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <stdlib.h>
#include <time.h>
#include <functional>
#include <iostream>
#include <list>
#include <mutex>
#include <thread>

using namespace std;

int a_ = 0;
std::mutex mutex_;  // lock，unlock，try_lock
/*
std::time_mutex
+ try_lock_for() // 阻塞直到超过指定的 timeout_duration 或得到锁，取决于何者先到来。成功获得锁时返回 true，否则返回false
+ try_lock_until() // 阻塞直至到指定的timeout_time或得到锁，取决于何者先到来。成功获得锁时返回 true，否则返回false
*/
std::mutex mutex2_;
std::condition_variable producer, consumer;  // 条件变量
std::list<int> data_;

void func(string id) {
  std::unique_lock<std::mutex> lk(mutex_, std::defer_lock);
  cout << "threadId = " << id;
  this_thread::sleep_for(100ms);
  lk.lock();
  cout << " " << ++a_ << endl;
}

class A {
 public:
  A() = default;
  void func(int i) {
    this_thread::sleep_for(1000ms);
    cout << "A::func(" << i << ")" << endl;
  }
};

void produce() {
  while (true) {
    this_thread::sleep_for(200ms);
    std::unique_lock<std::mutex> lk(mutex2_);
    while (data_.size() > 0) {
      producer.wait(lk);
    }

    srand(time(0));
    data_.push_back(rand());
    lk.unlock();
    consumer.notify_one();
  }
}

void consume() {
  while (true) {
    this_thread::sleep_for(190ms);
    std::unique_lock<std::mutex> lk(mutex2_);
    while (data_.size() == 0) {
      consumer.wait(lk);
    }
    std::cout << data_.front() << std::endl;
    data_.pop_back();
    lk.unlock();
    producer.notify_one();
  }
}

int main() {
  {
    std::thread t1{func, "1"};
    this_thread::yield();
    std::thread t2{func, "2"};

    t1.join();
    t2.join();
  }

  {
    std::shared_ptr<A> ptr = std::make_shared<A>();
    auto funcobj = std::bind(&A::func, ptr, std::placeholders::_1);
    std::thread t{funcobj, 101};
    t.join();
  }

  std::thread consumers[10], producers[10];
  for (int i = 0; i < 10; ++i) {
    consumers[i] = std::thread(consume);
    producers[i] = std::thread(produce);

    consumers[i].join();
    producers[i].join();
  }

  return 0;
}
