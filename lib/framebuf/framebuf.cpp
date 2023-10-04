#include "framebuf.h"

// it's macro time
#define swap(x, y)         \
    {                      \
        uint16_t temp = x; \
        x = y;             \
        y = temp;          \
    }

#define ABS(N) ((N < 0) ? (-N) : (N))

// Clear screen with color.
void fbuf_cls(FrameBuffer* fbuf, uint16_t color) {
    for (int i = 0; i < fbuf->w * fbuf->h; i++) {
        fbuf->buf[i] = color;
    }
}

// Get the color of the pixel at (x, y).
uint16_t fbuf_pget(FrameBuffer* fbuf, uint16_t x, uint16_t y) {
    uint16_t i = (y * fbuf->w + x);
    return fbuf->buf[i];
}

// Draw a pixel with color at (x, y).
void fbuf_pset(FrameBuffer* fbuf, uint16_t x, uint16_t y, uint16_t color) {
    uint16_t i = (y * fbuf->w + x);
    fbuf->buf[i] = color;
}

// from tinydraw.go and https://gist.github.com/bert/1085538

void fbuf_line(FrameBuffer* fbuf, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color) {
    // deal with vertical and horizontal lines
    // else, Breshnam
    if (x0 == x1) {
        if (y0 > y1) {
            swap(y0, y1);
        }
        for (; y0 <= y1; y0++) {
            fbuf_pset(fbuf, x0, y0, color);
        }
    } else if (y0 == y1) {
        if (x0 > x1) {
            swap(x0, x1);
        }
        for (; x0 <= x1; x0++) {
            fbuf_pset(fbuf, x0, y0, color);
        }
    } else {  // Breshnam
        int dx = ABS(x1 - x0), sx = x0 < x1 ? 1 : -1;
        int dy = -ABS(y1 - y0), sy = y0 < y1 ? 1 : -1;
        int err = dx + dy, e2; /* error value e_xy */

        for (;;) { /* loop */
            fbuf_pset(fbuf, x0, y0, color);
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

void fbuf_rect(FrameBuffer* fbuf, uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color) {
    for (int i = x; i < x + w; i++) {
        fbuf_line(fbuf, i, y, i, y + h - 1, color);
    }
}

void fbuf_rectb(FrameBuffer* fbuf, uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color) {
    fbuf_line(fbuf, x, y, x + w - 1, y, color);
    fbuf_line(fbuf, x, y, x, y + h - 1, color);
    fbuf_line(fbuf, x + w - 1, y, x + w - 1, y + h - 1, color);
    fbuf_line(fbuf, x, y + h - 1, x + w - 1, y + h - 1, color);
}

void fbuf_squ(FrameBuffer* fbuf, uint16_t x, uint16_t y, uint16_t k, uint16_t color) {
    fbuf_rect(fbuf, x, y, k, k, color);
}

void fbuf_squb(FrameBuffer* fbuf, uint16_t x, uint16_t y, uint16_t k, uint16_t color) {
    fbuf_rectb(fbuf, x, y, k, k, color);
}

void fbuf_circ(FrameBuffer* fbuf, uint16_t x, uint16_t y, uint16_t r, uint16_t color) {
    int16_t f = 1 - r;
    int16_t ddfx = 1;
    int16_t ddfy = -2 * r;

    int16_t x0 = 0;
    int16_t y0 = r;

    fbuf_line(fbuf, x, y - r, x, y + r, color);

    while (x0 < y0) {
        if (f >= 0) {
            y0--;
            ddfy += 2;
            f += ddfy;
        }
        x0++;
        ddfx += 2;
        f += ddfx;

        fbuf_line(fbuf, x + x0, y - y0, x + x0, y + y0, color);
        fbuf_line(fbuf, x + y0, y - x0, x + y0, y + x0, color);
        fbuf_line(fbuf, x - x0, y - y0, x - x0, y + y0, color);
        fbuf_line(fbuf, x - y0, y - x0, x - y0, y + x0, color);
    }
}

void fbuf_circb(FrameBuffer* fbuf, uint16_t x, uint16_t y, uint16_t r, uint16_t color) {
    int16_t f = 1 - r;
    int16_t ddfx = 1;
    int16_t ddfy = -2 * r;

    int16_t x0 = 0;
    int16_t y0 = r;

    fbuf_pset(fbuf, x, y + r, color);
    fbuf_pset(fbuf, x, y - r, color);
    fbuf_pset(fbuf, x + r, y, color);
    fbuf_pset(fbuf, x - r, y, color);
    while (x0 < y0) {
        if (f >= 0) {
            y0--;
            ddfy += 2;
            f += ddfy;
        }
        x0++;
        ddfx += 2;
        f += ddfx;

        fbuf_pset(fbuf, x + x0, y + y0, color);
        fbuf_pset(fbuf, x - x0, y + y0, color);
        fbuf_pset(fbuf, x + x0, y - y0, color);
        fbuf_pset(fbuf, x - x0, y - y0, color);
        fbuf_pset(fbuf, x + y0, y + x0, color);
        fbuf_pset(fbuf, x - y0, y + x0, color);
        fbuf_pset(fbuf, x + y0, y - x0, color);
        fbuf_pset(fbuf, x - y0, y - x0, color);
    }
}
