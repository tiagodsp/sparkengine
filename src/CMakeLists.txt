message("============================")
message("Scanning Modules...")

sbs_subdirlist(modules ${CMAKE_CURRENT_LIST_DIR})

foreach(module ${modules})
    #message(${module})
    add_subdirectory(${module})
endforeach()

