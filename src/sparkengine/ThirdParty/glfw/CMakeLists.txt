get_filename_component(LIBRARY_NAME ${CMAKE_CURRENT_LIST_DIR} NAME)
message("Importing library: ${LIBRARY_NAME}")

# set(extensions "c;cpp")

# foreach(extension ${extensions})
#     file(GLOB_RECURSE files ${CMAKE_CURRENT_LIST_DIR}/src "*.${extension}" NAME)
#     file(GLOB_RECURSE files ${CMAKE_CURRENT_LIST_DIR}/deps "*.${extension}" NAME)
#     list(APPEND sources ${files})
# endforeach()

# add_library(${LIBRARY_NAME} STATIC ${sources})

set(GLFW_BUILD_EXAMPLES 0)
set(GLFW_BUILD_TESTS 0)
set(GLFW_BUILD_DOCS 0)
set(GLFW_INSTALL 0)

add_subdirectory(./glfw_v3.3)

target_link_libraries(${LIBRARY_NAME} ${libraries})
#target_link_libraries(${LIBRARY_NAME} "-lX11 -lpthread")
target_include_directories(${LIBRARY_NAME} PUBLIC "./glfw_v3.3/deps")

#--------------------------------------------------------------------
# Detect and select backend APIs
#--------------------------------------------------------------------
# if (GLFW_USE_WAYLAND)
#     target_compile_definitions(${LIBRARY_NAME} PRIVATE _GLFW_WAYLAND)
#     message(STATUS "Using Wayland for window creation")
# elseif (GLFW_USE_OSMESA)
#     target_compile_definitions(${LIBRARY_NAME} PRIVATE _GLFW_OSMESA)
#     message(STATUS "Using OSMesa for headless context creation")
# elseif (WIN32)
#     target_compile_definitions(${LIBRARY_NAME} PRIVATE _GLFW_WIN32)
#     message(STATUS "Using Win32 for window creation")
# elseif (APPLE)
#     target_compile_definitions(${LIBRARY_NAME} PRIVATE _GLFW_COCOA)
#     message(STATUS "Using Cocoa for window creation")
# elseif (UNIX)
#     target_compile_definitions(${LIBRARY_NAME} PRIVATE _GLFW_X11)
#     message(STATUS "Using X11 for window creation")
# else()
#     message(FATAL_ERROR "No supported platform was detected")
# endif()