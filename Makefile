all: build section_2 section_3 section_20

build:
	mkdir build

section_2: 02_intro.cpp
	emcc -s WASM=1 -s EXPORTED_RUNTIME_METHODS='["cwrap"]' 02_intro.cpp -o build/02_intro.js
	#emcc 02_intro.cpp -o build/02_intro.html

section_3: 03_bigger_example.c
	emcc -O2 -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='["png"]' --preload-file 03_assets 03_bigger_example.c -o build/03_bigger_example.html

section_20: 20_baremetal.wat
	wat2wasm 20_baremetal.wat -o build/20_baremetal.wasm

clean:
	rm -r build/