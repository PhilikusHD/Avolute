cmake_minimum_required(VERSION 3.25.1)

# Set compiler
set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)

# Use the Ninja generator
set(CMAKE_GENERATOR "Ninja")

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set the output directories for different configurations
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib-${CMAKE_BUILD_TYPE})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib-${CMAKE_BUILD_TYPE})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin-${CMAKE_BUILD_TYPE})

project(Avolute)

# Common include directories for all platforms
include_directories(
    ${CMAKE_SOURCE_DIR}/Avolute/src
    ${CMAKE_SOURCE_DIR}/vendor/spdlog/include
    ${CMAKE_SOURCE_DIR}/vendor/stb
    ${CMAKE_SOURCE_DIR}/vendor/glm
    ${CMAKE_SOURCE_DIR}/vendor/SDL2/include
    ${CMAKE_SOURCE_DIR}/vendor/SDL_image
)

# Add subdirectories for other dependencies
add_subdirectory(vendor/spdlog vendor/spdlog)
add_subdirectory(vendor/glm)

# Build SDL2 as a static library
add_subdirectory(vendor/SDL2)
include_directories(${CMAKE_SOURCE_DIR}/vendor/SDL2/include)

file(GLOB_RECURSE SRC Avolute/*.cpp)
add_executable(Avolute ${SRC})

# Link SDL2, spdlog, and glm to your executable
target_link_libraries(Avolute PUBLIC SDL2main SDL2-static spdlog glm)

# Add subdirectory for SDL_image
add_subdirectory(vendor/SDL_image)

# Link SDL_image to your executable
target_link_libraries(Avolute PUBLIC SDL2_image)

# Compiler-specific options for Debug build
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(
        -g                      # Generate debug information
        -O0                     # Disable optimizations
        -Wall                   # Enable all compiler warnings
        -Wextra                 # Enable extra compiler warnings
        -glldb                  # Enable debug info tuning for the lldb debugger
        # -Werror               # Treat warnings as errors
    )

    # Define a preprocessor macro for debug builds
    target_compile_definitions(Avolute PRIVATE RV_DEBUG)

    # Add runtime checks for debug builds
    target_compile_options(Avolute PRIVATE -fstack-protector)
endif()

# Compiler-specific options for Release build
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_options(
        -O3                     # Enable aggressive optimizations
        -DNDEBUG                # Disable assertions
        # -flto                 # Enable Link Time Optimization (LTO) LTO currently causes problems, disabled for now
        # -march=native         # Generate code optimized for the host CPU architecture
        # -ffast-math           # Enable aggressive floating-point optimizations. Disabled due to its potential inaccuracy
        -funroll-loops          # Unroll loops to improve instruction-level parallelism
        -finline-functions      # Inline small functions for performance improvement
    )

    # Define a preprocessor macro for release builds
    target_compile_definitions(Avolute PRIVATE RV_RELEASE)

    # Strip symbols in release builds
    set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} -s")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -s")
endif()
