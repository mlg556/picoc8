#include <SDL2/SDL.h>
#include <stdio.h>

// #include "buffer.hpp"
#include <string>
using namespace std;

#include "framebuf.h"
// #include "sprite.c"

uint16_t buf[WH];

FrameBuffer fbuf = {buf};

SDL_Window *window;
SDL_Surface *screen_surface;
SDL_Event event;
uint32_t *pixels;
SDL_PixelFormat *format;

bool running = true;

const char *key_name;

uint32_t frame_count = 0;

uint32_t convert_color(uint16_t color) {
    uint8_t r, g, b;
    r = (color & 0xF800) >> 8;
    g = (color & 0x07E0) >> 3;
    b = (color & 0x1F) << 3;

    return SDL_MapRGB(format, r, g, b);
}

class Ship {
   public:
    int x, y, vx, vy;
    Ship() {
        x = W / 2;
        y = H / 2;
        vx = 0;
        vy = 0;
    }
};

Ship ship;

bool btn1 = false, btn2 = false, btn3 = false, btn4 = false;

int main(int argc, char *args[]) {
    // SDL init
    SDL_Init(SDL_INIT_EVERYTHING);

    window = SDL_CreateWindow("gamer", SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, W, H,
                              SDL_WINDOW_SHOWN);

    if (window == NULL) {
        printf("window err. %s", SDL_GetError);
        return 1;
    }

    screen_surface = SDL_GetWindowSurface(window);
    format = screen_surface->format;
    pixels = (uint32_t *)screen_surface->pixels;

    ship = Ship();

    // loop
    while (running) {
        // poll for events/keys
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_KEYDOWN:
                    key_name = SDL_GetKeyName(event.key.keysym.sym);
                    if (key_name[0] == 'A') {
                        btn1 = true;
                    }

                    if (key_name[0] == 'D') {
                        btn2 = true;
                    }

                    if (key_name[0] == 'W') {
                        btn3 = true;
                    }

                    if (key_name[0] == 'S') {
                        btn4 = true;
                    }

                    break;
                default:
                    break;
            }
        }
        // check for buttons here for SDL reasons.
        ship.vx = 0;
        ship.vy = 0;

        // printf("%s", btn1);

        if (btn1) {
            ship.vx = -3;
        }

        if (btn2) {
            ship.vx = 3;
        }

        if (btn3) {
            ship.vy = -3;
        }

        if (btn4) {
            ship.vy = 3;
        }

        ship.x += ship.vx;
        ship.y += ship.vy;

        btn1 = false;
        btn2 = false;
        btn3 = false;
        btn4 = false;

        fbuf_cls(&fbuf, BLACK);
        fbuf_blt(&fbuf, ship.x, ship.y, 16, 0, 32, 32);

        // start draw
        SDL_LockSurface(screen_surface);
        for (int i = 0; i < WH; i += 1) {
            uint32_t color = convert_color(fbuf.buf[i]);
            pixels[i] = color;
        }
        // end draw
        SDL_UnlockSurface(screen_surface);
        SDL_UpdateWindowSurface(window);

        SDL_Delay(30);
    }

    // destroy
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
