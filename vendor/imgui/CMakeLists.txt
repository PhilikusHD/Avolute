# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.25.1)

# Set the project name for ImGui
project(ImGui)

# Add the source files for ImGui
set(IMGUI_SOURCES
    imgui.cpp
    imgui_draw.cpp
    imgui_widgets.cpp
    imgui_demo.cpp
    imgui_tables.cpp
    imgui_stdlib.cpp
    backends/imgui_impl_sdl2.cpp
    backends/imgui_impl_sdlrenderer2.cpp
)

# Add the header files for ImGui
set(IMGUI_HEADERS
    imconfig.h
    imgui_internal.h
    imgui.h
    imstb_rectpack.h
    imstb_textedit.h
    imstb_truetype.h
    imgui_stdlib.h
    backends/imgui_impl_sdl2.cpp
    backends/imgui_impl_sdlrenderer2.cpp
)

# Create the ImGui static library
add_library(ImGui STATIC ${IMGUI_SOURCES} ${IMGUI_HEADERS})

# Add include directories for ImGui
target_include_directories(ImGui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
