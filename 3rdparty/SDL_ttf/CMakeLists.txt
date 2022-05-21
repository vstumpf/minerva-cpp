set(BUILD_SHARED_LIBS OFF)
set(BUILD_SAMPLES OFF)
set(TTF_DISABLE_INSTALL ON)

add_subdirectory(SDL_ttf EXCLUDE_FROM_ALL)

if (MSVC)
  target_compile_options(SDL2_ttf PRIVATE /MT$<$<CONFIG:Debug>:d>)
endif ()