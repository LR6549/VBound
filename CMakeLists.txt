cmake_minimum_required(VERSION 3.20)

project(Vbound LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_MODULE_PATH "F:/Dropbox/Dropbox/CompilerUndScripts/CMake/modules")
include(windowsLibs)

# ---- Executable ----
add_executable(${PROJECT_NAME}
        main.cpp
        #classes/audioHandler/audioHandler.cpp
        #classes/audioHandler/audioHandler.h++
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

if(MSVC)
    # Detect Windows SDK version automatically
    file(GLOB WIN_SDK_LIBS "C:/Program Files (x86)/Windows Kits/10/Lib/*/um/x64")
    list(GET WIN_SDK_LIBS -1 WIN_SDK_LIB_PATH)  # get latest version

    link_directories(${WIN_SDK_LIB_PATH})
endif()

target_compile_definitions(${PROJECT_NAME} PRIVATE SDL_STATIC)

# ---- Link libraries ----
target_link_libraries(${PROJECT_NAME} PRIVATE
        SDL3.lib
        SDL3_image.lib
        SDL3_mixer.lib
        SDL3_net.lib
        SDL3_ttf.lib
        SDL3_rtf.lib
        windowsLibs
        d3d11
        dxgi
        d3dcompiler
        gdi32
        user32
        winmm           # for timeBeginPeriod / timeEndPeriod
        setupapi        # for SetupDi* symbols
        cfgmgr32        # for CM_* symbols
        version         # for GetFileVersionInfo / VerQueryValue
        imm32           # for IME functions
)
