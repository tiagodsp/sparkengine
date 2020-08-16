cmake_minimum_required(VERSION 3.11)

#list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/sbs/cmake/cmakepch)

project(sparkengine C CXX)

set(CMAKE_CXX_STANDARD  17)

if(CMAKE_CXX_COMPILER MATCHES "em\\+\\+(-[a-zA-Z0-9.])?(.[a-zA-Z0-9.]*)?$")
  message(" * C++ compiler: Emscripten")
  set(CMAKE_CXX_COMPILER_ID "Emscripten")
else()
  message(" * C++ compiler: ${CMAKE_CXX_COMPILER}")
endif()

# Let's set compiler-specific flags
message("[${SBS_MODULE_NAME}] - Setting compilation options for ${CMAKE_CXX_COMPILER_ID}")
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    # G++
    add_compile_options(-Wall -Wextra -fvisibility=hidden -Wno-unused-parameter -Wno-unused-variable -fcxx-exceptions -Wno-documentation -Wno-reorder)
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "LLVM")
    #Clang
    add_compile_options(-Wall -Wextra -fvisibility=hidden -Wno-unused-parameter -Wno-unused-variable -fcxx-exceptions -Wno-documentation -Wno-reorder)
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    #Clang
    add_compile_options(-Wno-unused-parameter -Wno-unused-variable -Wno-documentation -Wno-reorder -Wno-c++98-compat-pedantic -Wno-documentation-unknown-command -Wno-deprecated-declarations -Wno-reserved-id-macro)
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    # MSVC
    add_compile_options(/EHsc /MTd /W2 /c)
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Emscripten")
    add_compile_options(-Wall -Wextra -fvisibility=hidden -Wno-unused-parameter -Wno-unused-variable -fcxx-exceptions -Wno-documentation -Wno-reorder)
    # Prefixes/suffixes for building
    set(CMAKE_STATIC_LIBRARY_PREFIX "")
    set(CMAKE_STATIC_LIBRARY_SUFFIX ".bc")
    set(CMAKE_EXECUTABLE_SUFFIX ".html")

    # Prefixes/suffixes for finding libraries
    set(CMAKE_FIND_LIBRARY_PREFIXES "")
    set(CMAKE_FIND_LIBRARY_SUFFIXES ".bc")
endif()





#set(CMAKE_CXX_FLAGS "-std=c++17")

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

##
#   Macro to list file within a directory.
##
function(addfileslist result dir extensions)
    set(filelist "")
    foreach(extension ${extensions})
        file(GLOB_RECURSE files "${dir}*.${extension}")
        set(filelist ${filelist} ${files})
    endforeach()
    set(${result} ${${result}} ${filelist} PARENT_SCOPE)
endfunction()

##
#   Function to help a configure a module.
##
function(sbs_add_module)
    set(option_params
        LIBRARY
        PROGRAM
        MODULE
        USE_PCH
    )
    set(lists_params
        DEPENDS
        EXTERNAL
        DEFINITIONS
        PUBLIC_INCLUDE_PATHS
        PRIVATE_INCLUDE_PATHS
        SOURCE_PATHS
    )
    cmake_parse_arguments(sbs_add_module "${option_params}" "${onevalue}" "${lists_params}" ${ARGN})

    
    get_filename_component(SBS_MODULE_NAME ${CMAKE_CURRENT_LIST_DIR} NAME)
    set(SBS_MODULE_DIR ${CMAKE_CURRENT_LIST_DIR})
    #set(SBS_MODULE_SOURCE_DIR ${SBS_MODULE_DIR})
    string(TOUPPER ${SBS_MODULE_NAME} SBS_MODULE_NAME_UPPER)
    set(SBS_MODULE_INTERMEDIATE_DIR ${SBS_MODULE_DIR}/intermediate)

    message("[${SBS_MODULE_NAME}] - Adding ${SBS_MODULE_NAME} module (${SBS_MODULE_DIR}).")

    # Add source files
    message("[${SBS_MODULE_NAME}] - Searching source files (${SBS_MODULE_DIR}).")
    foreach(sourcepath ${sbs_add_module_SOURCE_PATHS})
        addfileslist(module_source_files "${SBS_MODULE_DIR}/${sourcepath}" "cpp;cxx;c;cc")
    endforeach()
    foreach(file ${module_source_files})
        message("[${SBS_MODULE_NAME}] -    ++ ${file}")
    endforeach()
    
    #Set modules type;
    if(sbs_add_module_LIBRARY)
        message("[${SBS_MODULE_NAME}] - Building mode set as Library")
        add_library(${SBS_MODULE_NAME} SHARED ${module_source_files})
        target_compile_definitions(${SBS_MODULE_NAME} PRIVATE DLLEXPORT)
    elseif(sbs_add_module_PROGRAM)
        message("[${SBS_MODULE_NAME}] - Building mode set as Program")
        add_executable(${SBS_MODULE_NAME} ${module_source_files})
    endif()

    target_compile_definitions(${SBS_MODULE_NAME} PRIVATE ${SBS_MODULE_NAME_UPPER}_BUILD)

    #Configure intermediates
    message("[${SBS_MODULE_NAME}] - Configuring intermediate files.")
    configure_file(${CMAKE_SOURCE_DIR}/sbs/templates/api.gen.h.in ${SBS_MODULE_INTERMEDIATE_DIR}/${SBS_MODULE_NAME}.api.gen.h)
    
    

    # Add user defined definitions
    if(NOT ${sbs_add_module_DEFINITIONS})
        message("[${SBS_MODULE_NAME}] - Setting custom definitions:")
        foreach(definition ${sbs_add_module_DEFINITIONS})
            message("[${SBS_MODULE_NAME}] -    ++ ${definition}")
        endforeach()
        target_compile_definitions(${SBS_MODULE_NAME} PRIVATE ${sbs_add_module_DEFINITIONS})
    endif()

    # Add include paths
    foreach(public_inc_path ${sbs_add_module_PUBLIC_INCLUDE_PATHS})
        target_include_directories(${SBS_MODULE_NAME} BEFORE
            PUBLIC ${SBS_MODULE_DIR}/${public_inc_path}
        )
    endforeach()

    foreach(private_inc_path ${sbs_add_module_PRIVATE_INCLUDE_PATHS})
        target_include_directories(${SBS_MODULE_NAME} BEFORE
            PRIVATE ${SBS_MODULE_DIR}/${private_inc_path}
        )
    endforeach()

    target_include_directories(${SBS_MODULE_NAME} BEFORE
        PUBLIC ${SBS_MODULE_INTERMEDIATE_DIR}
    )
    
    #TODO - Check a reliable solution for add ThirdParty libraries.
    #Add ThirdParty dependencies;
    if(EXISTS ${SBS_MODULE_DIR}/ThirdParty)
        message("Third party folder for module ${SBS_MODULE_NAME} found. Checking...")
        file(GLOB folders RELATIVE ${SBS_MODULE_DIR}/ThirdParty ${SBS_MODULE_DIR}/ThirdParty/*)
        foreach(folder ${folders})
            add_subdirectory(${SBS_MODULE_DIR}/ThirdParty/${folder})
            #target_link_libraries(${SBS_MODULE_NAME} ${folder})
        endforeach()
    endif()


    #Add module dependencies;
    if(NOT ${sbs_add_module_DEPENDS})
        message("[${SBS_MODULE_NAME}] - Adding dependencies:")
        foreach(dependency ${sbs_add_module_DEPENDS})
            target_link_libraries(${SBS_MODULE_NAME} PUBLIC ${dependency})
            message("[${SBS_MODULE_NAME}] -    ++ ${dependency}")
        endforeach()
    endif()

    target_link_libraries(${SBS_MODULE_NAME} ${sbs_add_module_EXTERNAL})
    
    # Add PCH file into project if it is enabled.
    if(sbs_add_module_USE_PCH)
        if(EXISTS ${SBS_MODULE_SOURCE_DIR}/Public/${SBS_MODULE_NAME}.PCH.h)
            target_precompiled_header(${SBS_MODULE_NAME} ${SBS_MODULE_SOURCE_DIR}/Public/${SBS_MODULE_NAME}.PCH.h)
        endif()
    endif()

    
    
    # Set target output paths.
    set_target_properties(
        ${SBS_MODULE_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
        FOLDER "Modules"
    )
    

endfunction()

message("==========================================")
message("SPARK BUILD SYSTEM -- By Tiago Patrocinio")
message("==========================================")
add_subdirectory(${SPARKBUILDSYSTEM_SOURCE_DIR}/modules)