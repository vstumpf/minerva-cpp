set(SDL_SHARED OFF CACHE BOOL "Build a shared version of the library")

add_subdirectory(SDL2 EXCLUDE_FROM_ALL)

set(SDL2_SOURCE_DIR "${CMAKE_CURRENT_SRC_DIR}/SDL2")
set(SDL2_INCLUDE_DIR "${SDL2_SOURCE_DIR}/include")

if (MSVC)
  target_compile_options(SDL2-static PRIVATE /MT$<$<CONFIG:Debug>:d>)
endif ()
target_include_directories(SDL2-static PUBLIC  $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/SDL2/include>)
