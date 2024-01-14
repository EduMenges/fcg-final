CMAKE_MINIMUM_REQUIRED(VERSION 3.22)

project(fcg_final LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

if (WIN32)
    if (MINGW)
        set(LIBS ${PROJECT_SOURCE_DIR}/lib/libglfw3.a)
    elseif (MSVC)
        set(LIBS ${PROJECT_SOURCE_DIR}/lib-vc2022/glfw3.lib)
    else ()
        message(FATAL_ERROR "This project file only supports MINGW or MSVC toolchain on Windows.")
    endif ()
    list(APPEND LIBS gdi32 opengl32)
else ()
    find_package(OpenGL REQUIRED)
    find_package(X11 REQUIRED)
    set(LIBS ${PROJECT_SOURCE_DIR}/lib-linux/libglfw3.a X11 Xrandr Xinerama Xi Xxf86vm Xcursor GL)
endif ()

link_libraries(${LIBS})

find_package(glm CONFIG)
if (NOT glm_FOUND)
    FetchContent_Declare(
            glm
            GIT_REPOSITORY https://github.com/g-truc/glm.git
            GIT_TAG 0.9.9.8
    )
    FetchContent_MakeAvailable(glm)
endif ()

find_package(tinyobjloader CONFIG)
if (NOT tinyobjloader_FOUND)
    FetchContent_Declare(
            tinyobjloader
            GIT_REPOSITORY https://github.com/tinyobjloader/tinyobjloader.git
            GIT_TAG origin/release
    )
    FetchContent_MakeAvailable(tinyobjloader)
endif ()

FetchContent_Declare(
        expected
        GIT_REPOSITORY https://github.com/TartanLlama/expected.git
        GIT_TAG v1.1.0
)
set(EXPECTED_BUILD_PACKAGE OFF)
FetchContent_MakeAvailable(expected)

FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt.git
        GIT_TAG 10.2.1
)
FetchContent_MakeAvailable(fmt)
add_compile_definitions(_USE_MATH_DEFINES)

if (MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

add_compile_definitions(_USE_MATH_DEFINES)

add_subdirectory(glad)

add_subdirectory(src)
