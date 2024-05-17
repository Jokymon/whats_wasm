all: build 02_intro.cpp
	emcc -s WASM=1 -s EXPORTED_RUNTIME_METHODS='["cwrap"]' 02_intro.cpp -o build/02_intro.js
	#emcc 02_intro.cpp -o build/02_intro.html

build:
	mkdir build

clean:
	rm -r build/