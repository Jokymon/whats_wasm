# What is WASM?

This project provides an easy collection of various WASM-tools in a single Docker container
together with a set of example projects and a slide deck that guides you through WASM and the
possibilities of current WASM technology.

## Getting started

### Setup
My recommendation is to clone this project locally and startup a devcontainer. Note that the 
creation of devcontainer will take a little while. 
Once the container is running, open a shell in the container. First you need to build all the
example WASM modules and generated pages. This can be done with a simple call from the
workspace directory `/workspaces/whats_wasm/slides`:

```bash
make
```

Now you have to install the NPM packages needed for the **slidev**-based presentation:

```bash
cd slides/
npm install
```

### Running slides and examples

Once the steps of section *Setup* are done, you can start the slides using the script in the
workspace folder `/workspaces/whats_wasm/slides`:

```bash
./serve.sh
```

The slides will now be served on `localhost:3000`.

## What's in the container

The devcontainer is based on the Emscripten emSDK. On top of that, several additional tools are
installed to be able to play with various WASM technologies:

 - Rust toolchain with the `wasm32-unknown-unknown` and the `wasm32-wasi` backends
 - The WebAssembly Binary Toolkit (wabt) to work directly with web assemly modules
 - The Wasmer standalone runtime
 - Nginx for nicer serving of the slidev-based slides and the example pages with WASM modules

### Technical details

 - Nginx is used to forward IPv4 connections on port 3000 to the IPv6 based slidev-Node server.
 - Additionally Nginx serves the examples from the `examples/` folder on port 8000.