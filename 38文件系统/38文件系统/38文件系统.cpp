// 38文件系统.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。

#include <iostream>
#include <filesystem>
#include <fstream>
#include <sstream>

// C++17 支持 filesystem
namespace fs = std::filesystem;

// 读文件到string
std::string ReadFileIntoString(const fs::path& path) {
    std::ifstream ifile(path);
    std::ostringstream buf;
    char ch;
    while (buf && ifile.get(ch)) {
        buf.put(ch);
    }
    return buf.str();
}

int main() {
    // 返回当前工作路径
    std::cout << "Current path is: " << fs::current_path() << '\n';
    // 若存在则返回路径的根路径
    std::cout << "Current path is: " << fs::current_path().root_path() << '\n';
    // 若存在则返回路径的根名
    std::cout << "Current path is: " << fs::current_path().root_name() << '\n';

    fs::path path = fs::current_path();
    // 转换到字符串的原生路径名格式
    std::cout << path.string() << "\n";
    // 转换到字符串的通用路径名格式
    std::cout << path.generic_string() << "\n";

    // 连接路径，添加路径分隔符
    path /= "abc.txt";
    std::cout << path.string() << "\n";
    // 移除路径中的文件名
    path = path.remove_filename();
    std::cout << path.string() << "\n";
    // 创建新目录
    fs::create_directories(path);

    path /= "abc.txt";
    // 移除一个文件或空目录
    fs::remove(path);
 
    system("pause");
	return 0;

}
