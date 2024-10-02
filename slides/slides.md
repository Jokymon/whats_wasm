---
theme: default
# random image from a curated Unsplash collection by Anthony
# like them? see https://unsplash.com/collections/94734566/slidev
background: https://cover.sli.dev
# some information about your slides (markdown enabled)
title: What is WebAssembly
info: |
  ## Slidev Starter Template
  Presentation slides for developers.

  Learn more at [Sli.dev](https://sli.dev)
# apply unocss classes to the current slide
class: text-center
# https://sli.dev/features/drawing
drawings:
  persist: false
# slide transition: https://sli.dev/guide/animations.html#slide-transitions
transition: slide-left
# enable MDC Syntax: https://sli.dev/features/mdc
mdc: true
# take snapshot for each slide in the overview
overviewSnapshots: true
fonts:
  sans: Verdana
  mono: Fira Code
---

# Introduction to WebAssembly

A hacked together introduction to WASM concepts and programming

<!--
The last comment block of each slide will be treated as slide notes. It will be visible and editable in Presenter Mode along with the slide. [Read more in the docs](https://sli.dev/guide/syntax.html#notes)
-->

---

# Origins of WebAssembly (WASM)

- First appeared 2017
- First release 2019

According to the WebAssembly specification:

> ... Its main goal is to enable high performance **applications on the Web,**

but then also

> ... but it does not make any Web-specific assumptions or provide Web-specific
> features, so it can be employed in **other environments** as well.

<!--
You can have `style` tag in markdown to override the style for the current page.
Learn more: https://sli.dev/features/slide-scope-style
-->

<style>
/*h1 {
  background-color: #2B90B6;
  background-image: linear-gradient(45deg, #4EC5D4 10%, #146b8c 20%);
  background-size: 100%;
  -webkit-background-clip: text;
  -moz-background-clip: text;
  -webkit-text-fill-color: transparent;
  -moz-text-fill-color: transparent;
}*/
</style>

---

# Example with Emscripten/C (1)

For this example, a very simple C function was compiled to WASM using the 
Emscripten SDK. The code is very simple:

```c
#include <emscripten.h>

EMSCRIPTEN_KEEPALIVE
int my_add(int a, int b) {
    return a + b;
}
```

This code almost looks like regular C with the exception of the 
`EMSCRIPTEN_KEEPALIVE` macro and the special `#include`.

---

# Example with Emscripten/C (2)

To get this example built, the command line looks almost identical to calling another C/C++
compiler, like `gcc` or `clang`:

```bash
emcc 02_intro.c -o build/02_intro.js
```

The actual call has a couple of additional parameters that are needed, to make sure that the
single function in our `.c` file is not optimized away and that we also get the JS-function
`cwrap` which we need to create a wrapper around the C-function for easier use with Javascript.

---

# Example with Emscripten/C (3)

Notice that we ask `emcc` to generate a JS source file (`-o build/02_intro.js`). Emscripten however
will also generate the `.wasm` file. The JS file contains helper functions to simplify the
interaction between Javascript and the C/C++\-based WASM module. More of that will be explained
later.

---
layout: iframe-right
url: http://localhost:8000/02_zz_cpp_example.html
---

# Example with Emscripten/C (4)

Now we just need to include this in our website

```html
<script src="build/02_intro.js"></script>
```

... load the WASM module from Javascript ...

```javascript
Module.onRuntimeInitialized = _ => {
  my_add = Module.cwrap('my_add', 'number',
                        ['number', 'number']);
}
```

... and then just call it as a Javascript function

```javascript
let result = my_add(100, 20);
```

---
layout: iframe
url: http://localhost:8000/build/03_bigger_example.html
---
# Complex Emscripten example

---

# Basic concepts

At the very bottom, WebAssembly defines a very simple **Virtual Machine**. 

* Stack-based instruction set (i32/i64, f32/f64)
* Linear memory
    * single, 32-bit memory space 
        * proposal for up to 64 bit
        * proposal for multiple memories
* Interface defined through WASM modules
    * function signature types
    * imports and exports
    * global variables
    * tables

---

# WASM == JVM++? Or JVM-\-? 😜

| | **WASM** | **JVM** |
|-|------|-----|
| **Instructions** | ALU, control flow, memory access, table operations | ALU, control flow, object access and manipulation, special calls |
| **Data types** | `i32`, `i64`, `f32`, `f64`, `v128`, func references, extern opaque references | integer, long, short, byte, char, float, double, object references |
| **Interfacing** | Module, globals, memory imports/exports | JVM builtins, JNI |

---

# Baremetal WebAssembly Example

For a better understanding of what actually happens under the hood, it is helpful to look at an
example in "plain webassembly". Using the **wabt** toolchain we can also write WASM modules using
a textual representation of the WebAssembly "assembler language" that is structured like Lisp
programms.

<!-- I'm just cheating a little here, this is actually WAT-code, but Shiki has no formatter
for this. So we just use clojure that also uses s-expressions -->
```clojure
(module
  (func (export "wat_add") (param i32 i32) (result i32)
    local.get 0
    local.get 1
    i32.add))
```

---

# Languages compiling to WASM

A growing list of languages provides WASM targets:

stable(?):

- [C++ Emscripten](https://emscripten.org/index.html), [Rust](https://rustwasm.github.io/book/)
- [TinyGo, a Go variant](https://github.com/tinygo-org/tinygo) targetting a wide range of embedded devices, desktop OSes and WASM
- [Zig](https://ziglang.org/documentation/master/#WebAssembly) targetting various freestanding and OS-based targets as well as WASM
- C#, Python, Swift, TypeScript, Scala, Kotlin, ... (see some details in the [Fermyon project](https://developer.fermyon.com/wasm-languages/webassembly-language-support))

in development:
- [Grain](https://grain-lang.org/)
- [Virgil](https://github.com/titzer/virgil) targetting X86 MacOS, Linux, JAR files and WASM
- [MoonBit](https://www.moonbitlang.com/)

more:
[GitHub - awesome-wasm-langs](https://github.com/appcypher/awesome-wasm-langs)

---

# WASM for plugins

[Extism](https://extism.org/)
