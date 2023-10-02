#include "buffer.hpp"
#include "lib/framebuf/framebuf.h"

#include <SDL2/SDL.h>
#include <stdio.h>

uint16_t fbuf[WH];

BufferWindow<W, H> wnd = BufferWindow<W, H>();

SDL_PixelFormat *fmt = wnd.screenSurface->format;

uint32_t convert_color(uint16_t color)
{
    uint8_t r, g, b;
    r = (color & 0xF800) >> 8;
    g = (color & 0x07E0) >> 3;
    b = (color & 0x1F) << 3;

    return SDL_MapRGB(fmt, r, g, b);
}

int main(int argc, char *args[])
{
    // main loop
    while (!wnd.handle_keys()) {
        fbuf_fill(fbuf, WHITE);

        fbuf_line(fbuf, 10, 10, 60, 60, BLACK);

        // convert from framebuf to display
        wnd.startDraw();
        for (int i = 0; i < WH; i++) {
            wnd.pixels[i] = convert_color(fbuf[i]);
        }
        wnd.endDraw();
    }

    return 0;
}
