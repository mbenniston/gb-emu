FROM debian:bookworm AS gbemu-tests

WORKDIR /build
RUN apt-get update && apt-get -y install cmake clang clang-format clang-tidy
COPY . .
RUN find modules -type f \( -name "*.c" -o -name "*.h" -o -name "*.hpp" -o -name "*.cpp" \) -exec clang-format --dry-run --Werror {} +

RUN cmake . -DCMAKE_BUILD_TYPE=Debug -DENABLE_NATIVE_BUILD=OFF
RUN make
RUN ctest
