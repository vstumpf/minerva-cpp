set(SPDLOG_BUILD_TESTING OFF)

add_subdirectory(spdlog EXCLUDE_FROM_ALL)
if (MSVC)
    target_compile_options(spdlog PRIVATE /MT$<$<CONFIG:Debug>:d>)
endif ()