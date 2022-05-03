#include "./extern_tmpl.h"

template void gen<int>(int);

void test1() {
    gen(2);
}
