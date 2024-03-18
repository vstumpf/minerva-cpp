add_library(minerva-files)

target_sources(minerva-files PRIVATE
  "BmpResource.cpp"
  # "FlrResource.cpp"
  "Resource.cpp"
)

target_link_libraries(minerva-files PUBLIC 
  stb_image
)
