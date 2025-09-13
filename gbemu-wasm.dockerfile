FROM emscripten/emsdk:4.0.14

WORKDIR /build
RUN apt-get update && apt-get -y install cmake python3
RUN npm i -g typescript
COPY . .
RUN emcmake cmake . -DCMAKE_BUILD_TYPE=Release

# generate glue code for C++ (compiled into libgbweb-web) and JavaScript (added to --post-js)
RUN /emsdk/upstream/emscripten/tools/webidl_binder gbemuweb/bindings.idl glue

RUN emmake make

# extract object files from generated libraries (to avoid symbol stripping)
RUN mkdir libgbemu_objects libgbemu-web_objects
RUN emar --output libgbemu_objects -x libgbemu.a
RUN emar --output libgbemu-web_objects -x libgbemu-web.a

# compile to web assembly
RUN emcc \
    --post-js glue.js \
    -o gbemu.mjs \
    -s MODULARIZE \
    -s EXPORT_NAME=GBEmu \
    -s EXPORTED_FUNCTIONS="['_malloc', '_free']" \
    -s EXPORTED_RUNTIME_METHODS="['ccall', 'cwrap']" \
    -s TOTAL_STACK=512mb \
    libgbemu_objects/*.o \
    libgbemu-web_objects/*.o

FROM scratch
COPY --from=0 /build/gbemu.mjs /
COPY --from=0 /build/gbemu.wasm /
