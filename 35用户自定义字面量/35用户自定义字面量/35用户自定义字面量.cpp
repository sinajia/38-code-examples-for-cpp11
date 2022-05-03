// 35用户自定义字面量.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <thread>

using namespace std;

class RGB {
public:
    RGB(char const* v, size_t n) {
        const char* r = v, * g = nullptr, * b = nullptr, * p = nullptr;
        for (p = v; p != v + n; ++p) {
            if (*p == ',') {
                if (!g) {
                    r_ = atoi(string(r, p - r).c_str());
                    g = p + 1;
                    continue;
                }
                if (!b) {
                    g_ = atoi(string(g, p - g).c_str());
                    b = p + 1;
                    b_ = atoi(string(b, v + strlen(v) - b).c_str());
                    break;
                }
            }
        }
    }
    void func() {
        cout << "R=" << r_ << ",G=" << g_ << ",B=" << b_ << endl;
    }

    unsigned int r_ = 0;
    unsigned int g_ = 0;
    unsigned int b_ = 0;

};

RGB operator""_rgb(const char * v, size_t n) {
    return RGB(v, n);
}

int main()
{
    std::this_thread::sleep_for(100ms);
    // std::this_thread::sleep_for(std::chrono::milliseconds(100));

    RGB lrgb = "25,255,55"_rgb;

    lrgb.func();

    return 0;

}
