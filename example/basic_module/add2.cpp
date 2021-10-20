extern "C" {
#include "add1.h"
}

int add2(int v) { return add1(add1(v)); }
