#include "framebuf.h"

// it's macro time
#define swap(x, y)         \
    {                      \
        uint16_t temp = x; \
        x = y;             \
        y = temp;          \
    }

#define ABS(N) ((N < 0) ? (-N) : (N))

void fbuf_fill(uint16_t fbuf[], uint16_t color) {
    for (int i = 0; i < WH; i++) {
        fbuf[i] = color;  // clear to color
    }
}

void fbuf_setpixel(uint16_t fbuf[], uint16_t x, uint16_t y, uint16_t color) {
    uint16_t idx = (y * W + x);
    fbuf[idx] = color;
}

// from tinydraw.go and https://gist.github.com/bert/1085538

void fbuf_line(uint16_t fbuf[], uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color) {
    // deal with vertical and horizontal lines
    // else, Breshnam
    if (x0 == x1) {
        if (y0 > y1) {
            swap(y0, y1);
        }
        for (; y0 <= y1; y0++) {
            fbuf_setpixel(fbuf, x0, y0, color);
        }
    } else if (y0 == y1) {
        if (x0 > x1) {
            swap(x0, x1);
        }
        for (; x0 <= x1; x0++) {
            fbuf_setpixel(fbuf, x0, y0, color);
        }
    } else {  // Breshnam
        int dx = ABS(x1 - x0), sx = x0 < x1 ? 1 : -1;
        int dy = -ABS(y1 - y0), sy = y0 < y1 ? 1 : -1;
        int err = dx + dy, e2; /* error value e_xy */

        for (;;) { /* loop */
            fbuf_setpixel(fbuf, x0, y0, color);
            if (x0 == x1 && y0 == y1) break;
            e2 = 2 * err;
            if (e2 >= dy) {
                err += dy;
                x0 += sx;
            } /* e_xy+e_x > 0 */
            if (e2 <= dx) {
                err += dx;
                y0 += sy;
            } /* e_xy+e_y < 0 */
        }
    }
}