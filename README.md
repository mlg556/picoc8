# picoc8

experiments about drawing stuff in SDL, and then an actual TFT SPI, and maybe finally implementing a pico8/pyxel like embedded game engine thingy

# Notes

I'm thinking about making *only* the spritesheets etc. indexed, but the main framebuffer is uint16 (RGB565). otherwise I would have to do the lookup for each byte on SPI transmission. this way the lookup will be done when blitting the sprite to the "canvas". obviously an indexed color spritesheet will save on memory so we can have multiple.
