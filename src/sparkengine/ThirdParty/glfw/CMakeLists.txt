get_filename_component(LIBRARY_NAME ${CMAKE_CURRENT_LIST_DIR} NAME)
message("Importing library: ${LIBRARY_NAME}")

if(UNIX)
message("Importing libraries for LINUX platform.")
    set(platform "linux")
    set(extensions "a;so")
elseif(WIN32)
    message("Importing libraries for WINDOWS platform.")
    set(platform "win64")
    set(extensions "lib;dll")
endif()

foreach(extension ${extensions})
    file(GLOB_RECURSE libs ${CMAKE_CURRENT_LIST_DIR}/lib/${platform}/ "*.${extension}" NAME)
    message("libs: ${libs}")
    list(APPEND libraries ${libs})
endforeach()

message("Found pre-built libraries (*.${extensions}): ${libraries}")

add_library(${LIBRARY_NAME} STATIC "null.cpp")

target_link_libraries(${LIBRARY_NAME} ${libraries})
target_link_libraries(${LIBRARY_NAME} "-lX11 -lpthread")
target_include_directories(${LIBRARY_NAME} PUBLIC "./include")
