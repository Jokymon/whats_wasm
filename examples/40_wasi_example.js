import { Wasi } from "./wasi.js";

const wasi = new Wasi({
    stdin: prompt("Whats your name"),
    env: {
    },
    args: []
});

const { instance } = await WebAssembly.instantiateStreaming(fetch("./build/wasi_example.wasm"), {
    "wasi_snapshot_preview1": wasi
});
wasi.instance = instance;
instance.exports._start();
