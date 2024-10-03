#!/bin/bash

# Checkout trunk of the wabt repository
cd /tmp
git clone --recursive https://github.com/WebAssembly/wabt
cd wabt
git submodule update --init

# Build and install wabt
mkdir build
cd build
cmake ..
cmake --build .
cmake --install . --prefix "/opt/wabt"