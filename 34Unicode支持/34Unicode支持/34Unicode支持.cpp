// 34Unicode支持.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <codecvt>
#include <iomanip>

using namespace std;

int main()
{
    std::locale::global(std::locale("zh_CN"));

    wchar_t gbk[] = L"我爱北京天安门";

    cout << wcslen(gbk) * sizeof(wchar_t) << endl;

    wcout << gbk << endl;

    std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
    std::string utf8 = conv.to_bytes(gbk);

    cout << utf8.length() << endl;

    cout << setiosflags(ios::uppercase) << std::hex;

    for (char c : utf8) {
        cout << (unsigned)((unsigned char)c);
    }

    cout << endl;

    std::wstring wideStr = conv.from_bytes(utf8);

    // http://www.mytju.com/classcode/tools/encode_gb2312.asp
    for (wchar_t wc : wideStr) {
        cout << (unsigned)wc;
    }

    return 0;

}
