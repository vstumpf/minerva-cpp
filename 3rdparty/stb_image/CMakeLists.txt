enable_language(C)

set (STB_FILES
    "stb_image/stb_image.c"
)

add_library(stb_image ${STB_FILES})
target_include_directories(stb_image PUBLIC stb_image/include)

if (WIN32)
  target_compile_options(stb_image PRIVATE /MT$<$<CONFIG:Debug>:d>)
endif ()
