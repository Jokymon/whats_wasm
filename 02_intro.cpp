#include <emscripten.h>

extern "C" {
EMSCRIPTEN_KEEPALIVE
int my_add(int a, int b) {
    return a + b;
}
}