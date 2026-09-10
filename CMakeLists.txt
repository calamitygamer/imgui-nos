cmake_minimum_required(VERSION 3.20)
project(nostalgia VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# ── ImGui ──────────────────────────────────────────────────────────────────────
FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG        v1.91.1
    GIT_SHALLOW    TRUE
)
FetchContent_MakeAvailable(imgui)

set(IMGUI_DIR ${imgui_SOURCE_DIR})

add_library(imgui_lib STATIC
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/backends/imgui_impl_sdl2.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

target_include_directories(imgui_lib PUBLIC
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
)

# ── SDL2 (install via vcpkg: vcpkg install sdl2) ──────────────────────────────
find_package(SDL2 CONFIG REQUIRED)

# ── OpenGL ────────────────────────────────────────────────────────────────────
find_package(OpenGL REQUIRED)

target_link_libraries(imgui_lib PUBLIC SDL2::SDL2 OpenGL::GL)

# ── Executable ────────────────────────────────────────────────────────────────
add_executable(nostalgia WIN32
    src/main.cpp
    src/menu.cpp
)

target_include_directories(nostalgia PRIVATE
    src/
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
)

target_link_libraries(nostalgia PRIVATE
    imgui_lib
    SDL2::SDL2
    SDL2::SDL2main
    OpenGL::GL
)

if(MSVC)
    target_compile_options(nostalgia PRIVATE /W3 /utf-8)
    set_target_properties(nostalgia PROPERTIES
        VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
    )
endif()
