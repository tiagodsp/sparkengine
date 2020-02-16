IF NOT EXIST ./build (
    echo "Creating build directory..."
    mkdir "build"
)

cd "build"
cmake .. -DCMAKE_TOOLCHAIN_FILE="sbs/toolchains/Emscripten.cmake" -G Ninja
cd ..\bin
python -m http.server 8080
