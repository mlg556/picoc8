#include <stdint.h>

const uint16_t WHITE = 0xffff;
const uint16_t BLACK = 0x0000;
const uint16_t RED = 0xf800;
const uint16_t BLUE = 0x001f;
const uint16_t GREEN = 0x07e0;

static const int W = 128;
static const int H = 128;
static const int WH = W * H;
void fbuf_fill(uint16_t fbuf[], uint16_t color);
void fbuf_setpixel(uint16_t fbuf[], uint16_t x, uint16_t y, uint16_t color);
void fbuf_line(uint16_t fbuf[], uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color);

void fbuf_rect(uint16_t fbuf[], uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);
void fbuf_square(uint16_t fbuf[], uint16_t x, uint16_t y, uint16_t k, uint16_t color);

void fbuf_fillrect(uint16_t fbuf[], uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);
void fbuf_fillsquare(uint16_t fbuf[], uint16_t x, uint16_t y, uint16_t k, uint16_t color);

void fbuf_circle(uint16_t fbuf[], uint16_t x, uint16_t y, uint16_t r, uint16_t color);
void fbuf_fillcircle(uint16_t fbuf[], uint16_t x, uint16_t y, uint16_t r, uint16_t color);
