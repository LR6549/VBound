cmake_minimum_required(VERSION 3.20)

project(Vbound LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_MODULE_PATH "F:/Dropbox/Dropbox/CompilerUndScripts/CMake/modules")

include(windowsLibs)

add_executable(${PROJECT_NAME} main.cpp
        classes/audioHandler/audioHandler.cpp
        classes/audioHandler/audioHandler.h++
        classes/textureHandler/textureHandler.cpp
        classes/textureHandler/textureHandler.h++
        classes/chunkRenderer/chunkRenderer.cpp
        classes/chunkRenderer/chunkRenderer.h++
        classes/chunk/chunk.cpp
        classes/chunk/chunk.h++
        classes/block/block.cpp
        classes/block/block.h++
        classes/entity/entity.cpp
        classes/entity/entity.h++
)

set(CMAKE_PREFIX_PATH "F:/Dropbox/Dropbox/CPP_LIBARIES/windows")

find_package(SDL3 CONFIG REQUIRED)

target_compile_definitions(${PROJECT_NAME} PRIVATE SDL_STATIC)

target_link_options(${PROJECT_NAME} PRIVATE
        -static-libgcc
        -static-libstdc++
)

target_link_libraries(${PROJECT_NAME} PRIVATE
        SDL3::SDL3
        windowsLibs
)
