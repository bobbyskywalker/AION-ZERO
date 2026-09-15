#include "draw.hpp"

#include <cstdint>

constexpr uint16_t SPRITE_TRANSPARENT = 0x0000;

void drawTile(
    display::LcdDisplay& display,
    const unsigned char* image,
    const uint16_t x,
    const uint16_t y,
    const uint16_t imageWidth,
    const uint16_t imageHeight
) {
    display.drawSprite(image, x, y, imageWidth, imageHeight);
}

void drawSprite(const uint8_t* image, const int x, const int y, const uint8_t width, const uint8_t height) { {
        for (int py = 0; py < height; py++) {
            for (int px = 0; px < width; px++) {

                const int index = (py * width + px) * 2;

                const uint16_t color =
                    static_cast<uint16_t>(image[index + 1]) << 8 |
                    image[index];

                if (color == SPRITE_TRANSPARENT) {
                    continue;
                }

                Paint_SetPixel(x + px, y + py, color);
            }
        }
    }
}