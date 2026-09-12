#include "display.hpp"

display::LcdDisplay::LcdDisplay(const uint8_t orientation) {
    DEV_Module_Init();
    LCD_1IN44_Init(orientation);
    Paint_NewImage(framebuffer_, WIDTH, HEIGHT, ROTATE_0, WHITE);
    Paint_SetScale(65);
}

void display::LcdDisplay::clear(const uint16_t color) {
    Paint_Clear(color);
}

void display::LcdDisplay::update() {
    LCD_1IN44_Display(reinterpret_cast<UWORD *>(framebuffer_));
}

display::LcdDisplay::~LcdDisplay() {
    DEV_Module_Exit();
}

void display::LcdDisplay::drawString(
    const uint16_t x,
    const uint16_t y,
    const char* text,
    const sFONT& font,
    const uint16_t colorForeground,
    const uint16_t colorBackground)
{
    Paint_DrawString_EN(
        x,
        y,
        text,
        const_cast<sFONT*>(&font),
        colorForeground,
        colorBackground
    );
}
