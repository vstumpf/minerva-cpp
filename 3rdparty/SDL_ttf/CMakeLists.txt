set(BUILD_SHARED_LIBS OFF)
set(BUILD_SAMPLES OFF)

add_subdirectory(SDL_ttf EXCLUDE_FROM_ALL)

set(SDL_TTF_INCLUDE_DIR "${CMAKE_CURRENT_SRC_DIR}/SDL_ttf")

if (MSVC)
  target_compile_options(SDL2_ttf PRIVATE /MT$<$<CONFIG:Debug>:d>)
  target_compile_options(freetype PRIVATE /MT$<$<CONFIG:Debug>:d>)
endif ()