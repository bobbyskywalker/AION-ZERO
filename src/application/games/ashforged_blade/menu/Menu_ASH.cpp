#include "Menu_ASH.hpp"

#include "../util/draw.hpp"
#include "menu_assets.hpp"

void Menu_ASH::runMenu(display::LcdDisplay & display) {
    this->draw(display);
}

void Menu_ASH::draw([[maybe_unused]] display::LcdDisplay & display) const {
    display.clear(BLACK);

    const auto drawMenu = [](const unsigned char variant[]) {
        for (uint16_t y = 0; y < display::HEIGHT; y++) {
            for (uint16_t x = 0; x < display::WIDTH; x++) {
                const uint32_t index = (y * display::WIDTH + x) * 2;

                const uint16_t color =
                    static_cast<uint16_t>(variant[index]) |
                    static_cast<uint16_t>(variant[index + 1]) << 8;

                drawPixel(x, y, color);
            }
        }
    };

    if (this->currentOption_ == static_cast<uint8_t>(MENU_ASH_OPTIONS::PLAY)) {
        drawMenu(PLAY_SELECTED);
    } else if (this->currentOption_ == static_cast<uint8_t>(MENU_ASH_OPTIONS::EXIT)) {
        drawMenu(EXIT_SELECTED);
    }
}

void Menu_ASH::updateOption(const uint8_t dir) {
    constexpr uint8_t size = std::size(menuOptions_);

    if (dir == 0) {
        currentOption_ = currentOption_ == 0 ? size - 1 : currentOption_ - 1;
    } else if (dir == 1) {
        currentOption_ = (currentOption_ + 1) % size;
    }
}
