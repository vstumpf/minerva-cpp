file(
    GLOB_RECURSE
    MINERVA_FILES
    *.cpp
    *.hpp
    *.c
    *.h
)

add_executable(
    ${PROJECT_NAME}
    ${MINERVA_FILES}
)

set_target_properties(
    ${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    COMPILE_FLAGS "${WARNING_FLAGS}"
)

# Add clang-tidy
if(MINERVA_USE_CLANG_TIDY AND CLANG_TIDY_EXE)
    set_target_properties(
        ${PROJECT_NAME} PROPERTIES
        CXX_CLANG_TIDY "${DO_CLANG_TIDY}"
    )
endif()

foreach(source IN LISTS MINERVA_FILES)
    get_filename_component(source_path "${source}" PATH)
    string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "" rel_source_path "${source_path}")
    string(REPLACE "/" "\\" source_path_msvc "${rel_source_path}")
    source_group("${source_path_msvc}" FILES "${source}")
endforeach()

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR})
target_include_directories(${PROJECT_NAME} PUBLIC
    ${SDL2_TTF_INCLUDE_DIRS}
    ${OPENGL_INCLUDE_DIR}
)

# Link libraries and add include directories for third parties
target_link_libraries(${PROJECT_NAME} 
    glm
    glad
    spdlog
    nlohmann_json
    ${OPENGL_LIBRARIES}
)
if (WIN32)
    target_link_libraries(${PROJECT_NAME}
        wsock32
        ws2_32
    )
endif ()

target_compile_options(${PROJECT_NAME} PRIVATE "$<$<CONFIG:DEBUG>:-DMINERVA_DEBUG>")

if (MSVC)
    set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
    target_compile_options(${PROJECT_NAME} PRIVATE /MT$<$<CONFIG:Debug>:d>)
    target_compile_options(${PROJECT_NAME} PRIVATE "/MP")
    target_compile_options(${PROJECT_NAME} PRIVATE "/we4701")
endif ()
