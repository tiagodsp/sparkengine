#
# Toolchain for cross-compiling to JS using Emscripten
#
# Modify EMSCRIPTEN_PREFIX to your liking; use EMSCRIPTEN environment variable
# to point to it or pass it explicitly via -DEMSCRIPTEN_PREFIX=<path>.
#
#  mkdir build-emscripten && cd build-emscripten
#  cmake .. -DCMAKE_TOOLCHAIN_FILE=../toolchains/generic/Emscripten.cmake
#

set(CMAKE_SYSTEM_NAME Emscripten)

# Help CMake find the platform file
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/../modules ${CMAKE_MODULE_PATH})

# Give a hand to first-time Windows users
if(CMAKE_HOST_WIN32)
    if(CMAKE_GENERATOR MATCHES "Visual Studio")
        message(FATAL_ERROR "Visual Studio project generator doesn't support cross-compiling to Emscripten. Please use -G Ninja or other generators instead.")
    endif()
endif()

if(NOT EMSCRIPTEN_PREFIX)
    if(DEFINED ENV{EMSCRIPTEN})
        file(TO_CMAKE_PATH "$ENV{EMSCRIPTEN}" EMSCRIPTEN_PREFIX)
    # On Homebrew the sysroot is here, however emcc is also available in
    # /usr/local/bin. It's impossible to figure out the sysroot from there, so
    # try this first
    elseif(EXISTS "/usr/local/opt/emscripten/libexec/emcc")
        set(EMSCRIPTEN_PREFIX "/usr/local/opt/emscripten/libexec")
    # Look for emcc in the path as a last resort
    else()
        find_file(_EMSCRIPTEN_EMCC_EXECUTABLE emcc)
        if(EXISTS ${_EMSCRIPTEN_EMCC_EXECUTABLE})
            get_filename_component(EMSCRIPTEN_PREFIX ${_EMSCRIPTEN_EMCC_EXECUTABLE} DIRECTORY)
        else()
            set(EMSCRIPTEN_PREFIX "/usr/lib/emscripten")
        endif()
        mark_as_advanced(_EMSCRIPTEN_EMCC_EXECUTABLE)
    endif()
endif()

set(EMSCRIPTEN_TOOLCHAIN_PATH "${EMSCRIPTEN_PREFIX}/system")

if(CMAKE_HOST_WIN32)
    set(EMCC_SUFFIX ".bat")
else()
    set(EMCC_SUFFIX "")
endif()
set(CMAKE_C_COMPILER "${EMSCRIPTEN_PREFIX}/emcc${EMCC_SUFFIX}")
set(CMAKE_CXX_COMPILER "${EMSCRIPTEN_PREFIX}/em++${EMCC_SUFFIX}")
set(CMAKE_AR "${EMSCRIPTEN_PREFIX}/emar${EMCC_SUFFIX}" CACHE FILEPATH "Emscripten ar")
set(CMAKE_RANLIB "${EMSCRIPTEN_PREFIX}/emranlib${EMCC_SUFFIX}" CACHE FILEPATH "Emscripten ranlib")

set(CMAKE_FIND_ROOT_PATH ${CMAKE_FIND_ROOT_PATH}
    "${EMSCRIPTEN_TOOLCHAIN_PATH}"
    "${EMSCRIPTEN_PREFIX}")

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

# Otherwise FindCorrade fails to find _CORRADE_MODULE_DIR. Why the heck is this
# not implicit is beyond me.
set(CMAKE_SYSTEM_PREFIX_PATH ${CMAKE_FIND_ROOT_PATH})

# Since some unspecified release, -s WASM=1 is the default, so we need to
# explicitly say -s WASM=0 to use asm.js. The *_INIT variables are available
# since CMake 3.7, so it won't work in earlier versions. Sorry.
cmake_minimum_required(VERSION 3.7)
set(CMAKE_CXX_FLAGS_INIT "-s WASM=1")
set(CMAKE_EXE_LINKER_FLAGS_INIT "-s WASM=1")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-DNDEBUG -O3")
set(CMAKE_EXE_LINKER_FLAGS_RELEASE_INIT "-O3 --llvm-lto 1")

# Set a global EMSCRIPTEN variable that can be used in client CMakeLists.txt to
# detect when building using Emscripten. The go-to way when using Corrade is
# to check CORRADE_TARGET_* variables, this is mainly to support 3rd party
# projects.
set(EMSCRIPTEN 1 CACHE BOOL "If true, we are targeting Emscripten output." FORCE)

# Prefixes/suffixes for building
set(CMAKE_STATIC_LIBRARY_PREFIX "")
set(CMAKE_STATIC_LIBRARY_SUFFIX ".bc")
set(CMAKE_EXECUTABLE_SUFFIX ".js")

# Prefixes/suffixes for finding libraries
set(CMAKE_FIND_LIBRARY_PREFIXES "")
set(CMAKE_FIND_LIBRARY_SUFFIXES ".bc")

# Disable annoying warning about absolute includes
string(APPEND CMAKE_CXX_FLAGS " -Wno-warn-absolute-paths")

# Setting this prevents CMake from doing a relink on install (that is because
# of RPath, which is of no use on this platform). This also allows us to use
# Ninja, finally.
set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)

# Emscripten has Clang underneath and it supports -isystem. For some reason the
# compiler autodetection fails to detect this and this cause overwhelming
# amount of spam messages when including third-party headers.
set(CMAKE_INCLUDE_SYSTEM_FLAG_CXX "-isystem")