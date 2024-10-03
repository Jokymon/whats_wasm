FROM emscripten/emsdk:3.1.68

RUN apt-get update

# Install dependencies for Rust and Wasmer
RUN apt-get install -y \
    build-essential \
    curl

# Install Rust
RUN curl https://sh.rustup.rs -sSf | bash -s -- -y
ENV PATH="/root/.cargo/bin:${PATH}"

RUN rustup target add wasm32-unknown-unknown
RUN rustup target add wasm32-wasi

RUN cargo install wasm-pack wasm-bindgen-cli

# Install Wasmer lightweight WASM runtime
RUN curl https://get.wasmer.io -sSfL | sh

# Install wabt
COPY install_wabt.sh .
RUN ./install_wabt.sh
ENV PATH="/opt/wabt/bin:${PATH}"

# Tools for slide presentation
RUN apt-get install -y nginx
COPY nginx.conf /etc/nginx/sites-available/default
