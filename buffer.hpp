#pragma once

/*
  A simple SDL2-based framebuffer for graphics programming.
  (Giulio Zausa, 2019)

  Usage:

  auto wnd = BufferWindow<WIDTH, HEIGHT>();
  auto time = 0.0;
  while (!wnd.handle_keys()) {
    wnd.startDraw();

    // Clear with black
    memset(wnd.pixels, 0, WIDTH * HEIGHT * 4);

    // Draw your graphics here, framebuffer is in wnd.pixels, RGBA uint32 format

    wnd.endDraw();
    time += wnd.getDeltaTime();
  }
*/

#include <SDL2/SDL.h>

template <size_t width, size_t height>
class BufferWindow
{

public:
    uint32_t *pixels;
    SDL_Window *window;
    SDL_Surface *screenSurface;
    SDL_PixelFormat *fmt;

    BufferWindow()
    {
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        } else {
            window = SDL_CreateWindow("gamer", SDL_WINDOWPOS_UNDEFINED,
                                      SDL_WINDOWPOS_UNDEFINED, width, height,
                                      SDL_WINDOW_SHOWN);
            if (window == NULL) {
                printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            } else {
                screenSurface = SDL_GetWindowSurface(window);
                pixels = (uint32_t *)screenSurface->pixels;
            }
        }
    }

    ~BufferWindow()
    {
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    auto handle_keys()
    {
        SDL_Event e;
        // int keysPointer = 0;
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                return true;
            }
        }

        return false;
    }

    void startDraw() { SDL_LockSurface(screenSurface); }

    void endDraw()
    {
        SDL_UnlockSurface(screenSurface);
        SDL_UpdateWindowSurface(window);
    }
};
