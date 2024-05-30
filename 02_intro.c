#include <emscripten.h>

// In this example we only compile a simple library (which will be turned into a
// WASM module), containing a single function. Since this function isn't used anywhere
// else on the C/C++ side, Emscripten would optimize it away and remove it. The
// EMSCRIPTEN_KEEPALIVE macro prevents this optimization. 
EMSCRIPTEN_KEEPALIVE
int my_add(int a, int b) {
    return a + b;
}
