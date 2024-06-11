import { Wasi } from "./wasi.js";

const wasi = new Wasi({
    stdin: prompt("Whats your name"),
    env: {
    },
    args: []
});

const { instance } = await WebAssembly.instantiateStreaming(fetch("40_wasi_example/target/wasm32-wasi/debug/wasi_example.wasm"), {
    "wasi_snapshot_preview1": wasi
});
wasi.instance = instance;
instance.exports._start();
