#include <SDL2/SDL.h>
#include <stdio.h>

#include "buffer.hpp"
#include "lib/framebuf/framebuf.h"

typedef struct Ball {
    int16_t x, y, r;
    int16_t vx, vy;
} Ball;

Ball b = {.x = 40, .y = 40, .r = 10, .vx = -2, .vy = 3};

uint16_t fbuf[WH];

BufferWindow<W, H> wnd = BufferWindow<W, H>();
SDL_PixelFormat *fmt = wnd.screenSurface->format;

double dt = wnd.getDeltaTime();

uint32_t convert_color(uint16_t color) {
    uint8_t r, g, b;
    r = (color & 0xF800) >> 8;
    g = (color & 0x07E0) >> 3;
    b = (color & 0x1F) << 3;

    return SDL_MapRGB(fmt, r, g, b);
}

int main(int argc, char *args[]) {
    // main loop
    while (!wnd.handle_keys()) {
        // if (dt < 0.3) {
        //     dt = wnd.getDeltaTime();
        //     continue;
        // }

        fbuf_fill(fbuf, WHITE);
        // x, y
        fbuf_line(fbuf, 10, 10, 20, 10, GREEN);
        fbuf_line(fbuf, 10, 10, 10, 20, RED);

        // draw ball
        fbuf_fillcircle(fbuf, b.x, b.y, b.r, BLUE);

        // update ball
        b.x += b.vx;
        b.y += b.vy;

        // collide
        if (b.x < b.r) {
            b.x = b.r;
            b.vx *= -1;
        }
        if (b.y < b.r) {
            b.y = b.r;
            b.vy *= -1;
        }
        if (b.x > W - b.r) {
            b.x = W - b.r;
            b.vx *= -1;
        }
        if (b.y > H - b.r) {
            b.y = H - b.r;
            b.vy *= -1;
        }

        // convert from framebuf to display
        wnd.startDraw();
        for (int i = 0; i < WH; i += 1) {
            uint32_t color = convert_color(fbuf[i]);
            wnd.pixels[i] = color;
        }
        wnd.endDraw();

        dt = wnd.getDeltaTime();

        SDL_Delay(20);
    }

    return 0;
}
