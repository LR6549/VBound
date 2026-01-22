cmake_minimum_required(VERSION 3.20)
project(Vbound LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


list(APPEND CMAKE_MODULE_PATH "F:/Dropbox/Dropbox/CompilerUndScripts/CMake/modules")
include(windowsLibs)

set_source_files_properties(F:/Dropbox/Dropbox/CPP_LIBARIES/windows/src/glad.c PROPERTIES LANGUAGE CXX)

# ---- Executable ----
add_executable(${PROJECT_NAME}
        main.cpp
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
        F:/Dropbox/Dropbox/CPP_LIBARIES/windows/src/glad.c
        classes/player/player.cpp
        classes/player/player.h++
        classes/camera/camera.cpp
        classes/camera/camera.h++
        classes/mesh/Mesh.cpp
        classes/mesh/Mesh.h++
        classes/textRenderer/TextRenderer.cpp
        classes/textRenderer/TextRenderer.h++
)

target_compile_definitions(${PROJECT_NAME} PRIVATE SDL_STATIC)

# ---- Link libraries ----
target_link_libraries(${PROJECT_NAME} PRIVATE
        windowsLibs
        SDL3.lib
        SDL3_image.lib
        SDL3_mixer.lib
        SDL3_net.lib
        SDL3_ttf.lib
        SDL3_rtf.lib
        opengl32
        user32
        winmm
        setupapi
        cfgmgr32
        version
        imm32
)
