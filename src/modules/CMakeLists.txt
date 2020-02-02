message("============================")
message("Scanning Modules...")

sbs_subdirlist(modules ${CMAKE_CURRENT_LIST_DIR})

foreach(module ${modules})
    #message(${module})
    if(EXISTS "${CMAKE_CURRENT_LIST_DIR}/${module}/CMakeLists.txt")
        message("Scanning ${module}/CMakeLists.txt")
        add_subdirectory(${module})
    endif()
endforeach()

