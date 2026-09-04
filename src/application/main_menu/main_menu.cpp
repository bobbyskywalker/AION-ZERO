#include "main_menu.hpp"
extern "C" {
#include <string.h>
}

[[noreturn]] void MainMenu::loop() {
    const auto text = "AION-ZERO";

    const uint16_t text_width = strlen(text) * Font12.Width;
    const uint16_t x = (display::WIDTH - text_width) / 2;

    const uint16_t y_offset = Font12.Height + 5;
    const uint16_t y = 0 + y_offset;

    bool titleInv = true;

    while (true) {
        this->display_.clear(BLACK);
        if (titleInv) {
            this->display_.drawString(x, y, text, Font12, BLACK, WHITE);
            titleInv = false;
        } else {
            this->display_.drawString(x, y, text, Font12, WHITE, BLACK);
            titleInv = true;
        }
        this->display_.update();
        sleep_ms(1000);
    }
}
