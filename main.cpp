#include <SDL2/SDL.h>
#include <stdio.h>

#include "buffer.hpp"
#include "lib/framebuf/framebuf.h"
// #include "sprite.c"

const int W = 128;
const int H = 128;

const int WH = 128 * 128;

uint16_t buf[WH];

FrameBuffer fbuf = {.buf = buf, .w = W, .h = H};

BufferWindow<W, H> wnd = BufferWindow<W, H>();
SDL_PixelFormat *fmt = wnd.screenSurface->format;

uint32_t frame_count = 0;

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
        for (int i = 0; i < 16; i++) {
            fbuf_rect(&fbuf, 0, 8 * i, 128, 8, fbuf_palette[i]);
        }

        // x, y
        // fbuf_line(&fbuf, 10, 10, 20, 10, fbuf_palette[8]);
        // fbuf_line(&fbuf, 10, 10, 10, 20, fbuf_palette[11]);

        // fbuf_circ(&fbuf, 40, 40, 10, fbuf_palette[10]);

        // convert from framebuf to display
        wnd.startDraw();
        for (int i = 0; i < WH; i += 1) {
            uint32_t color = convert_color(fbuf.buf[i]);
            wnd.pixels[i] = color;
        }
        wnd.endDraw();
        frame_count++;
        SDL_Delay(20);
    }

    return 0;
}
