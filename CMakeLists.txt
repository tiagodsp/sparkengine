cmake_minimum_required(VERSION 3.11)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/sbs/cmake/cmakepch)

project(sparkengine C CXX CXXPCH)

set(CMAKE_CXX_FLAGS "-std=c++17")

#Variable definitions:
set(SPARKBUILDSYSTEM_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)

#set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
SET(CMAKE_BUILD_RPATH "./")

macro(sbs_subdirlist result curdir)
    file(GLOB children RELATIVE ${curdir} ${curdir}/*)
    foreach(child ${children})
        if(IS_DIRECTORY ${curdir}/${child})
            list(APPEND dirlist ${child})
        endif()
    endforeach()
    set(${result} ${dirlist})
endmacro()

macro(getfileslist result dir extensions)
    set(found_files "")
    foreach(extension ${extensions})
        file(GLOB_RECURSE files NAME ${dir} "*.${extension}")
        message("found: ${files}")
        set(found_files ${found_files} ${files})
    endforeach()
    set(${result} ${found_files})
endmacro()

function(sbs_add_module)
    set(options LIBRARY PROGRAM USE_PCH)
    set(dependencies DEPENDS EXTERNAL DEFINITIONS)
    cmake_parse_arguments(sbs_add_module "${options}" "${onevalue}" "${dependencies}" ${ARGN})

    
    get_filename_component(SBS_MODULE_NAME ${CMAKE_CURRENT_LIST_DIR} NAME)
    set(SBS_MODULE_DIR ${CMAKE_CURRENT_LIST_DIR})
    set(SBS_MODULE_SOURCE_DIR ${SBS_MODULE_DIR}/Source)
    string(TOUPPER ${SBS_MODULE_NAME} SBS_MODULE_NAME_UPPER)
    set(SBS_MODULE_INTERMEDIATE_DIR ${SBS_MODULE_DIR}/intermediate)

    message("Adding ${SBS_MODULE_NAME} module (${SBS_MODULE_DIR}).")
    
    #Configure intermediates
    configure_file(${CMAKE_SOURCE_DIR}/sbs/templates/api.gen.h.in ${SBS_MODULE_INTERMEDIATE_DIR}/${SBS_MODULE_NAME}.api.gen.h)
    
    getfileslist(module_source_files ${SBS_MODULE_SOURCE_DIR}/Private "cpp;cxx;c;cc")

    #Set modules type;
    if(sbs_add_module_LIBRARY)
        message("Building mode of module ${SBS_MODULE_NAME} set as Library")
        add_library(${SBS_MODULE_NAME} SHARED ${module_source_files})
    elseif(sbs_add_module_PROGRAM)
        message("Building mode of module ${SBS_MODULE_NAME} set as Program")
        add_executable(${SBS_MODULE_NAME} ${module_source_files})
    endif()

    
    target_compile_definitions(${SBS_MODULE_NAME} PRIVATE ${sbs_add_module_FLAGS})

    target_include_directories(${SBS_MODULE_NAME}
        PUBLIC ${SBS_MODULE_INTERMEDIATE_DIR}
        PUBLIC ${SBS_MODULE_SOURCE_DIR}/Public
        PRIVATE ${SBS_MODULE_SOURCE_DIR}/Private
    )

    # Let's set compiler-specific flags
    if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
        # G++
        target_compile_options(${SBS_MODULE_NAME} PRIVATE -Wall -Wextra -fvisibility=hidden -Wno-unused-parameter -Wno-unused-variable)
    elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "LLVM")
        #Clang
        target_compile_options(${SBS_MODULE_NAME} PRIVATE -Wall -Wextra -fvisibility=hidden -Wno-unused-parameter -Wno-unused-variable)    
    elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
        # MSVC
        target_compile_options(${SBS_MODULE_NAME} PRIVATE /EHsc /MTd /W2 /c)
        # Set the DLLEXPORT variable to export symbols
    endif()
    
    target_compile_definitions(${SBS_MODULE_NAME} PRIVATE WIN_EXPORT)

  

    #Add module dependencies;
    foreach(dependency ${sbs_add_module_DEPENDS})
        target_link_libraries(${SBS_MODULE_NAME} ${dependency})
    endforeach()

    #Add ThirdParty dependencies;
    if(EXISTS ${SBS_MODULE_DIR}/ThirdParty)
        message("Third party folder for module ${SBS_MODULE_NAME} found. Checking...")
        file(GLOB folders RELATIVE ${SBS_MODULE_DIR}/ThirdParty ${SBS_MODULE_DIR}/ThirdParty/*)
        foreach(folder ${folders})
            add_subdirectory(${SBS_MODULE_DIR}/ThirdParty/${folder})
            target_link_libraries(${SBS_MODULE_NAME} ${folder})
        endforeach()
    endif()
    
    if(sbs_add_module_USE_PCH)
        if(EXISTS ${SBS_MODULE_SOURCE_DIR}/Public/${SBS_MODULE_NAME}.PCH.h)
            target_precompiled_header(${SBS_MODULE_NAME} ${SBS_MODULE_SOURCE_DIR}/Public/${SBS_MODULE_NAME}.PCH.h)
        endif()
    endif()

    #target_link_libraries(${SBS_MODULE_NAME} ${sbs_add_module_EXTERNAL})
    

    set_target_properties(
        ${SBS_MODULE_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/
        RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/bin/
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
    )




endfunction()


add_subdirectory(${SPARKBUILDSYSTEM_SOURCE_DIR})