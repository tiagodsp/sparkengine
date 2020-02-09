get_filename_component(LIBRARY_NAME ${CMAKE_CURRENT_LIST_DIR} NAME)
message("Importing library: ${LIBRARY_NAME}")


set(extensions "c;cpp;h")

foreach(extension ${extensions})
    file(GLOB_RECURSE files ${CMAKE_CURRENT_LIST_DIR}/src/ "*.${extension}" NAME)
    file(GLOB_RECURSE files ${CMAKE_CURRENT_LIST_DIR}/include/ "*.${extension}" NAME)
    list(APPEND sources "${files}")
endforeach()

add_library(${LIBRARY_NAME} STATIC ${sources})
target_include_directories(${LIBRARY_NAME} PUBLIC "./include")
set_target_properties(${LIBRARY_NAME} PROPERTIES LINKER_LANGUAGE C)

set_target_properties(${LIBRARY_NAME} PROPERTIES FOLDER "ThirdParty")