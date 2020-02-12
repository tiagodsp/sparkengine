get_filename_component(LIBRARY_NAME ${CMAKE_CURRENT_LIST_DIR} NAME)
message("Importing library: ${LIBRARY_NAME}")

add_subdirectory(./glfw_v3.3)

 # Let's set compiler-specific flags
 if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    # G++
    target_compile_options(glfw BEFORE PRIVATE -MTd)
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "LLVM")
    #Clang
    target_compile_options(glfw BEFORE PRIVATE -MTd)    
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    # MSVC
    target_compile_options(glfw BEFORE PRIVATE /MTd)
    # Set the DLLEXPORT variable to export symbols
endif()

target_compile_definitions(glfw PUBLIC "GLFW_INCLUDE_NONE")

set_target_properties(${LIBRARY_NAME} PROPERTIES FOLDER "ThirdParty")