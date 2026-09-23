#ifndef AION_ZERO_FMW_DRAW_HPP
#define AION_ZERO_FMW_DRAW_HPP

#include <cstdint>
#include "../../../../display/display.hpp"

void drawTile(
    display::LcdDisplay& display,
    const unsigned char* image,
    uint16_t x,
    uint16_t y,
    uint16_t imageWidth,
    uint16_t imageHeight
);

void drawSprite(
    const uint8_t* image,
    int x,
    int y,
    uint8_t width,
    uint8_t height
);

void drawPixel(
    uint16_t x,
    uint16_t y,
    uint16_t color
);
#endif //AION_ZERO_FMW_DRAW_HPP