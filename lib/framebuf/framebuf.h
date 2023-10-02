#include <stdint.h>

const uint16_t WHITE = 0xFFFF;
const uint16_t BLACK = 0x0000;
const uint16_t RED = 0xF800;
const uint16_t BLUE = 0x07E0;
const uint16_t GREEN = 0x001F;

static const int W = 128;
static const int H = 128;
static const int WH = W * H;
// void fbuf_fill(uint16_t buf[], uint16_t color);
void fbuf_fill(uint16_t fbuf[], uint16_t color);
void fbuf_setpixel(uint16_t fbuf[], uint16_t x, uint16_t y, uint16_t color);
void fbuf_line(uint16_t fbuf[], uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color);
