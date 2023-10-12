#include <stdint.h>

#define W 240
#define H 320
#define WH 240 * 320

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef int16_t i16;
typedef int32_t i32;

const u16 WHITE = 0xffff;
const u16 BLACK = 0x0000;
const u16 RED = 0xf800;
const u16 BLUE = 0x001f;
const u16 GREEN = 0x07e0;

// pico8 palette. converted from 24 to 16 bits
const u16 fbuf_palette[16] = {
    0x0000,
    0x194a,
    0x792a,
    0x042a,
    0xaa86,
    0x5aa9,
    0xc618,
    0xff9d,
    0xf809,
    0xfd00,
    0xff64,
    0x0726,
    0x2d7f,
    0x83b3,
    0xfbb5,
    0xfe75,
};
// the FrameBuffer struct holds a pointer to the allocated buffer
// and w/h info, which is used in drawing methods.
typedef struct FrameBuffer {
    u16* buf;
} FrameBuffer;

// method api is inspired from kitao/pyxel

// Clear screen with color.
void fbuf_cls(FrameBuffer* fbuf, u16 color);

// Get the color of the pixel at (x, y).
u16 fbuf_pget(FrameBuffer* fbuf, u16 x, u16 y);

// Draw a pixel with color at (x, y).
void fbuf_pset(FrameBuffer* fbuf, u16 x, u16 y, u16 color);

// Draw a line with color from (x0, y0) to (x1, y1).
void fbuf_line(FrameBuffer* fbuf, u16 x0, u16 y0, u16 x1, u16 y1, u16 color);

// Draw a rectangle of width w, height h and color at (x, y).
void fbuf_rect(FrameBuffer* fbuf, u16 x, u16 y, u16 w, u16 h, u16 color);

// Draw the outline of a rectangle of width w, height h and color at (x, y).
void fbuf_rectb(FrameBuffer* fbuf, u16 x, u16 y, u16 w, u16 h, u16 color);

// Draw a square of side k and color at (x, y).
void fbuf_squ(FrameBuffer* fbuf, u16 x, u16 y, u16 k, u16 color);

// Draw the outline of a square of side k and color at (x, y).
void fbuf_squb(FrameBuffer* fbuf, u16 x, u16 y, u16 k, u16 color);

// Draw a circle of radius r and color at (x, y).
void fbuf_circ(FrameBuffer* fbuf, u16 x, u16 y, u16 r, u16 color);

// Draw the outline a circle of radius r and color at (x, y).
void fbuf_circb(FrameBuffer* fbuf, u16 x, u16 y, u16 r, u16 color);

// Copy the region of size (w, h) from (u, v) of the sprite bank to (x, y). Black is transparent
void fbuf_blt(FrameBuffer* fbuf, u16 x, u16 y, u16 u, u16 v, u16 w, u16 h);
