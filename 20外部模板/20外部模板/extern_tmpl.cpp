#include "./extern_tmpl.h"

template void gen<int>(int); // ��ǰ����ʵ������ģ��

void test1() {
    gen(2);
}
