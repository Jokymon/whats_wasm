all: build section_2 section_3 section_20 section_40

build:
	mkdir examples/build

section_2: 02_intro.c
	emcc -s WASM=1 -s EXPORTED_RUNTIME_METHODS='["cwrap"]' 02_intro.c -o examples/build/02_intro.js

section_3: 03_bigger_example.c
	emcc -O2 -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='["png"]' --preload-file 03_assets 03_bigger_example.c -o examples/build/03_bigger_example.html

section_20: 20_baremetal.wat
	wat2wasm 20_baremetal.wat -o examples/build/20_baremetal.wasm

section_40: 40_wasi_example/src/main.rs
	cd 40_wasi_example; cargo build
	cd 40_wasi_example; cargo build --target wasm32-wasi
	cp 40_wasi_example/target/wasm32-wasi/debug/wasi_example.wasm examples/build


clean:
	rm -r examples/build/