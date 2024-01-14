project(stb)
add_library(stb STATIC stb_image.cpp stb_image.h)
target_include_directories(stb PUBLIC ${PROJECT_SOURCE_DIR})