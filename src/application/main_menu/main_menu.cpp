#include "main_menu.hpp"
extern "C" {
#include <string.h>
}

[[nodiscard]] ModuleSwitchRequest MainMenu::loop() {
    const uint16_t initialY = Font16.Height + 5;
    const uint16_t initialOptionsY = initialY * 3;

    this->display_.clear(BLACK);

    const uint16_t titleWidth = strlen(TITLE) * Font16.Width;
    uint16_t x = (display::WIDTH - titleWidth) / 2;
    display_.drawString(x, initialY, TITLE, Font16, BLACK, WHITE);

    for (std::size_t i = 0; i < options.size(); ++i) {
        constexpr uint8_t optionOffset = 20;

        const uint16_t text_width = static_cast<uint16_t>(strlen(options[i])) * Font12.Width;
        x = (display::WIDTH - text_width) / 2;
        const uint16_t y = initialOptionsY + static_cast<uint16_t>(i) * optionOffset;

        display_.drawString(x, y, options[i], Font12, BLACK, WHITE);
    }

    display_.update();

    return ModuleSwitchRequest::None;
}

void MainMenu::onEnter() {/**/}