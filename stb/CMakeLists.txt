project(stb LANGUAGES C)
add_library(stb stb_image.c)
target_include_directories(stb PUBLIC ${PROJECT_SOURCE_DIR}/..)