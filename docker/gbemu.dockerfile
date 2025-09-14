FROM emscripten/emsdk:4.0.2 AS gbemu

WORKDIR /build
RUN apt-get update && apt-get -y install cmake python3 clang-format clang-tidy
RUN npm i -g typescript
COPY . .

RUN emcmake cmake . -DCMAKE_BUILD_TYPE=Release -DENABLE_NATIVE_BUILD=OFF -DENABLE_BROWSER_LIBRARY=ON

# generate glue code for C++ (compiled into libgbweb-web) and JavaScript (added to --post-js)
RUN /emsdk/upstream/emscripten/tools/webidl_binder modules/gbemu-bindings/bindings.idl glue

RUN emmake make

# extract object files from generated libraries (to avoid symbol stripping)
RUN mkdir libgbemu_objects libgbemu-web_objects
RUN emar --output libgbemu_objects -x ./modules/gbemu/libgbemu.a
RUN emar --output libgbemu-web_objects -x ./modules/gbemu-bindings/libgbemu-bindings.a

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

FROM node:22-bullseye AS webapp

WORKDIR /build

COPY ./applications/gbemu-web/package.json .
COPY ./applications/gbemu-web/package-lock.json .
RUN npm ci
COPY ./applications/gbemu-web .
COPY ./modules/gbemu-bindings/bindings.idl .

RUN npm run lint:format
RUN npm run lint:css

RUN npm run gbemuweb:generate-types

RUN npm run lint

COPY --from=gbemu /build/gbemu.mjs /build/src
COPY --from=gbemu /build/gbemu.wasm /build/src


COPY .git .git
RUN npm run docs:generate-release-notes
RUN npm run build

FROM scratch
COPY --from=webapp /build/dist /dist
