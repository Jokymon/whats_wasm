# Example with Emscripten/C++

For this example, a very simple C++ function was compiled to WASM using the Emscripten SDK. Just
like when using a native C/C++ compiler, we run a compilation step similar to the following:

```bash
emcc 02_intro.cpp -o build/02_intro.js
```

The actual call has a couple of additional parameters that are needed to make sure that the
single function in our `.cpp` file is not optimized away and that we also get the JS-function
`cwrap` which we need to create a wrapper around the C-function for easier use with Javascript.