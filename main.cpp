//__ VBound Main CPP File



#include <iostream>
#include <DirectX/directx/d3d12.h>

//++ SDL3 Libs:
#include <SDL3/SDL.h>
#include <SDL3/SDL3_image/SDL_image.h>
#include <SDL3/SDL3_ttf/SDL_ttf.h>

#include <windows.h>
#include <chrono>

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("SDL3 + DX12 Rotating Triangle Test", 800, 600, SDL_WINDOW_MAXIMIZED | SDL_WINDOW_RESIZABLE);
    // --- Get HWND from SDL3 ---
    SDL_PropertiesID props = SDL_GetWindowProperties(window);
    HWND hwnd = (HWND)SDL_GetPointerProperty(props, SDL_PROP_WINDOW_WIN32_HWND_POINTER, nullptr);



    // --- Main loop ---
    bool running = true;
    SDL_Event event;
    auto start = std::chrono::high_resolution_clock::now();
    auto end = std::chrono::high_resolution_clock::now();

    while(running) {
        while(SDL_PollEvent(&event)){
            if(event.type==SDL_EVENT_QUIT) running=false;
        }
        start = std::chrono::high_resolution_clock::now();

        end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff = end - start;
        std::cout << "FPS: " << 1.0 / diff.count() << "\n";
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
}