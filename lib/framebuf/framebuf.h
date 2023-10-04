#include <stdint.h>

const uint16_t WHITE = 0xffff;
const uint16_t BLACK = 0x0000;
const uint16_t RED = 0xf800;
const uint16_t BLUE = 0x001f;
const uint16_t GREEN = 0x07e0;

// the FrameBuffer struct holds a pointer to the allocated buffer
// and w/h info, which is used in drawing methods.
typedef struct FrameBuffer {
    uint16_t* buf;
    const uint16_t w, h;
} FrameBuffer;

// method api is inspired from kitao/pyxel

// Clear screen with color.
void fbuf_cls(FrameBuffer* fbuf, uint16_t color);

// Get the color of the pixel at (x, y).
uint16_t fbuf_pget(FrameBuffer* fbuf, uint16_t x, uint16_t y);

// Draw a pixel with color at (x, y).
void fbuf_pset(FrameBuffer* fbuf, uint16_t x, uint16_t y, uint16_t color);

// Draw a line with color from (x0, y0) to (x1, y1).
void fbuf_line(FrameBuffer* fbuf, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color);

// Draw a rectangle of width w, height h and color at (x, y).
void fbuf_rect(FrameBuffer* fbuf, uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);

// Draw the outline of a rectangle of width w, height h and color at (x, y).
void fbuf_rectb(FrameBuffer* fbuf, uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);

// Draw a square of side k and color at (x, y).
void fbuf_squ(FrameBuffer* fbuf, uint16_t x, uint16_t y, uint16_t k, uint16_t color);

// Draw the outline of a square of side k and color at (x, y).
void fbuf_squb(FrameBuffer* fbuf, uint16_t x, uint16_t y, uint16_t k, uint16_t color);

// Draw a circle of radius r and color at (x, y).
void fbuf_circ(FrameBuffer* fbuf, uint16_t x, uint16_t y, uint16_t r, uint16_t color);

// Draw the outline a circle of radius r and color at (x, y).
void fbuf_circb(FrameBuffer* fbuf, uint16_t x, uint16_t y, uint16_t r, uint16_t color);

// void fbuf_blt(FrameBuffer* fbuf, uint16_t x, uint16_t y, uint16_t u, uint16_t v, uint16_t w, uint16_t h);
