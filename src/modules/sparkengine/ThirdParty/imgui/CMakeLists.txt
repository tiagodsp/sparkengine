get_filename_component(LIBRARY_NAME ${CMAKE_CURRENT_LIST_DIR} NAME)
message("Importing library: ${LIBRARY_NAME}")


set(extensions "c;cpp")

foreach(extension ${extensions})
    file(GLOB_RECURSE files ${CMAKE_CURRENT_LIST_DIR}/src/ "*.${extension}" NAME)
    list(APPEND sources "${files}")
endforeach()

add_library(${LIBRARY_NAME} STATIC ${sources})
target_include_directories(${LIBRARY_NAME} PUBLIC "./src")
target_link_libraries(${LIBRARY_NAME} PRIVATE freetype2)
set_target_properties(${LIBRARY_NAME} PROPERTIES LINKER_LANGUAGE CXX)

