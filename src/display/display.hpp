#ifndef AION_ZERO_FMW_DISPLAY_HPP
#define AION_ZERO_FMW_DISPLAY_HPP

#include <cstdint>

extern "C" {
#include "GUI_Paint.h"
#include "LCD_1in44.h"
#include "DEV_Config.h"
}

namespace display {
    constexpr uint16_t WIDTH = 128;
    constexpr uint16_t HEIGHT = 128;
    constexpr uint8_t BYTES_PER_PIXEL = 2;
    constexpr std::size_t FRAMEBUFFER_SIZE = WIDTH * HEIGHT * BYTES_PER_PIXEL;

    class LcdDisplay {
    private:
        UBYTE framebuffer_[FRAMEBUFFER_SIZE]{};

    public:
        explicit LcdDisplay(uint8_t orientation);
        ~LcdDisplay();
        void clear(uint16_t color) ;

        void drawString(
            uint16_t x,
            uint16_t y,
            const char *text,
            const sFONT &font,
            uint16_t colorForeground,
            uint16_t colorBackground
        );

        void drawSprite(
            const unsigned char *image,
            uint16_t x,
            uint16_t y,
            uint16_t imageWidth,
            uint16_t imageHeight
        );

        void update();
    };
}

#endif // AION_ZERO_FMW_DISPLAY_HPP