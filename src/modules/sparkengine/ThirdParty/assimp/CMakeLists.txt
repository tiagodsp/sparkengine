get_filename_component(LIBRARY_NAME ${CMAKE_CURRENT_LIST_DIR} NAME)
message("Importing library: ${LIBRARY_NAME}")

add_subdirectory(./assimp501)

 # Let's set compiler-specific flags
 if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    # G++
    target_compile_options(assimp BEFORE PRIVATE -MD)
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "LLVM")
    #Clang
    target_compile_options(assimp BEFORE PRIVATE -MDd)    
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    #Clang
    target_compile_options(assimp BEFORE PRIVATE -MDd -Wno-everything)   
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    # MSVC
    #target_compile_options(assimp BEFORE PRIVATE /MTd)
    # Set the DLLEXPORT variable to export symbols
endif()

set_target_properties(assimp PROPERTIES ASSIMP_BUILD_TESTS OFF)

#target_compile_definitions(glfw PUBLIC "GLFW_INCLUDE_NONE")
target_include_directories(${LIBRARY_NAME} PUBLIC "./assimp501/include")
set_target_properties(${LIBRARY_NAME} PROPERTIES FOLDER "ThirdParty")