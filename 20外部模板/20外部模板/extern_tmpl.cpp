#include "./extern_tmpl.h"

template void gen<int>(int); // 提前声明实例化的模板

void test1() {
    gen(2);
}
