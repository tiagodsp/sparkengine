get_filename_component(LIBRARY_NAME ${CMAKE_CURRENT_LIST_DIR} NAME)
message("Importing library: ${LIBRARY_NAME}")

# project(LIB_${LIBRARY_NAME})

# add subdirectory as custom target
add_subdirectory(./src)
# target_link_libraries(sparkengine PRIVATE ${LIBRARY_NAME})

# add_custom_target(LIB_${LIBRARY_NAME})
# add_dependencies(LIB_${LIBRARY_NAME} ShaderConductor)

target_include_directories(${LIBRARY_NAME} PRIVATE "./src/Include")
set_target_properties(${LIBRARY_NAME} PROPERTIES FOLDER "ThirdParty")