// 31chrono库.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <chrono>

using namespace std;
int main() {
    const auto millisec_since_epoch =
        std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
    auto sec_since_epoch = std::chrono::duration_cast<std::chrono::seconds>(millisec_since_epoch);
    cout << millisec_since_epoch.count() << endl;
    cout << sec_since_epoch.count() << endl;
    return 0;
}
