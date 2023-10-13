#include "framebuf.h"

#include <string.h>  // used only for strlen

#include "sprite.h"

// font used is "Tom Thumb 4x6 from https://robey.lag.net/2010/01/23/tiny-monospace-font.html by Robey Pointer <robey@lag.net> LICENSE: CC0 or CC-BY 3.0
// no modifications made, just embedded into a 120x180 png

// it's macro time
#define swap(x, y)    \
    {                 \
        u16 temp = x; \
        x = y;        \
        y = temp;     \
    }

#define ABS(N) ((N < 0) ? (-N) : (N))

// framebuf width is W
static u32 fbuf_at(u16 x, u16 y) {
    return (y * W + x);
}

// spritesheet width is WW
static u32 spr_at(u16 x, u16 y) {
    return (y * WW + x);
}

// Clear screen with color.
void fbuf_cls(FrameBuffer* fbuf, u16 color) {
    for (int i = 0; i < W * H; i++) {
        fbuf->buf[i] = color;
    }
}

// Get the color of the pixel at (x, y).
u16 fbuf_pget(FrameBuffer* fbuf, u16 x, u16 y) {
    u32 i = fbuf_at(x, y);
    return fbuf->buf[i];
}

// Draw a pixel with color at (x, y).
void fbuf_pset(FrameBuffer* fbuf, u16 x, u16 y, u16 color) {
    u32 i = fbuf_at(x, y);
    if (i <= WH)
        fbuf->buf[i] = color;
}

// from tinydraw.go and https://gist.github.com/bert/1085538

void fbuf_line(FrameBuffer* fbuf, u16 x0, u16 y0, u16 x1, u16 y1, u16 color) {
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

void fbuf_rect(FrameBuffer* fbuf, u16 x, u16 y, u16 w, u16 h, u16 color) {
    for (int i = x; i < x + w; i++) {
        fbuf_line(fbuf, i, y, i, y + h - 1, color);
    }
}

void fbuf_rectb(FrameBuffer* fbuf, u16 x, u16 y, u16 w, u16 h, u16 color) {
    fbuf_line(fbuf, x, y, x + w - 1, y, color);
    fbuf_line(fbuf, x, y, x, y + h - 1, color);
    fbuf_line(fbuf, x + w - 1, y, x + w - 1, y + h - 1, color);
    fbuf_line(fbuf, x, y + h - 1, x + w - 1, y + h - 1, color);
}

void fbuf_squ(FrameBuffer* fbuf, u16 x, u16 y, u16 k, u16 color) {
    fbuf_rect(fbuf, x, y, k, k, color);
}

void fbuf_squb(FrameBuffer* fbuf, u16 x, u16 y, u16 k, u16 color) {
    fbuf_rectb(fbuf, x, y, k, k, color);
}

void fbuf_circ(FrameBuffer* fbuf, u16 x, u16 y, u16 r, u16 color) {
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

void fbuf_circb(FrameBuffer* fbuf, u16 x, u16 y, u16 r, u16 color) {
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

// Copy the region of size (w, h) from (u, v) of the sprite bank to (x, y). Black is transparent
// the spritesheet is 120x160, so it's scaled up when blitting to the framebuffer.
void fbuf_blt(FrameBuffer* fbuf, u16 x, u16 y, u16 u, u16 v, u16 w, u16 h) {
    u16 pix;

    // BAD CODE. this should all be done in pset
    x = x * 2;
    y = y * 2;

    for (int j = 0; j < h; j++) {
        for (int i = 0; i < w; i++) {
            pix = sprite0[spr_at(u + i, v + j)];
            if (pix != 0) {  // 0 is transparent black
                // paint 4 pixels to upscale
                fbuf_pset(fbuf, x + (2 * i), y + 2 * j, fbuf_palette[pix]);
                fbuf_pset(fbuf, x + (2 * i) + 1, y + 2 * j, fbuf_palette[pix]);
                fbuf_pset(fbuf, x + (2 * i), y + 2 * j + 1, fbuf_palette[pix]);
                fbuf_pset(fbuf, x + (2 * i) + 1, y + 2 * j + 1, fbuf_palette[pix]);
            }
        }
    }
}

// writes char c at (x,y) with color.
void fbuf_char(FrameBuffer* fbuf, char c, u16 x, u16 y, u16 color) {
    // it's like blt, but to print a char with arbitrary color
    // (not just the color in the spritesheet), we must do extra

    u16 u, v, pix;
    if (c == ' ') {
        // (0, 0) holds the empty sprite, so we use that for space
        u = 0;
        v = 0;
    } else if (c > 127) {
        // write the DEL character
        u = 64;
        v = 304;
    } else {
        // the spritesheet is in the ASCII order but in a 30x4 table, starting at (0, 136)
        // subtract 33 so '!' is 0
        // then find the coordinates from the linear index
        // multiply by cell width and add the table starting coordinates
        c = c - 33;
        u = (c % 30) * 4;
        v = (c / 30) * 6 + 136;
    }

    // chars are 4x6
    for (int j = 0; j < 6; j++) {
        for (int i = 0; i < 4; i++) {
            pix = sprite0[spr_at(u + i, v + j)];
            if (pix != 0) {  // 0 is transparent black
                // paint 4 pixels to upscale
                fbuf_pset(fbuf, x + (2 * i), y + 2 * j, color);
                fbuf_pset(fbuf, x + (2 * i) + 1, y + 2 * j, color);
                fbuf_pset(fbuf, x + (2 * i), y + 2 * j + 1, color);
                fbuf_pset(fbuf, x + (2 * i) + 1, y + 2 * j + 1, color);
            }
        }
    }
}

void fbuf_text(FrameBuffer* fbuf, const char* text, u16 x, u16 y, u16 color) {
    for (int i = 0; i < strlen(text); i++) {
        fbuf_char(fbuf, text[i], x + 8 * i, y, color);
    }
}
