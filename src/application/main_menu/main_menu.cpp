#include "main_menu.hpp"

#include "../../engine/input.hpp"

extern "C" {
#include <string.h>
}

[[nodiscard]] ModuleSwitchRequest MainMenu::loop() {
    while (true) {
        this->processMenuState();
        display_.update();
        sleep_ms(16);
        printf("current option: %d\n", selectedOption_);
    }

    return ModuleSwitchRequest::None;
}

void MainMenu::processMenuState() {
    switch (currentState_) {
        case MAIN_MENU_STATE::IN_ROOT:
            processRootMenuState();
            break;
        case MAIN_MENU_STATE::IN_GAMES_MENU:
            // todo
            break;
        case MAIN_MENU_STATE::IN_SETTINGS:
            // todo
            break;
        case MAIN_MENU_STATE::IN_ABOUT:
            processAboutMenuState();
            break;
        default:
            break;
    }
}

void MainMenu::processRootMenuState() {

    this->drawRootMenu();

    if (InputEngine::wasButtonPressed(InputEngine::BUTTONS.at(MAIN_MENU_BUTTONS::BUTTON_UP))
        && selectedOption_ > 0) {
        --selectedOption_;
        }
    if (InputEngine::wasButtonPressed(InputEngine::BUTTONS.at(MAIN_MENU_BUTTONS::BUTTON_DOWN))
        && selectedOption_ < options_.size() - 1) {
        ++selectedOption_;
        }
    if (InputEngine::wasButtonPressed(InputEngine::BUTTONS.at(MAIN_MENU_BUTTONS::BUTTON_ENTER))) {
        if (selectedOption_ == 0) {
            currentState_ = MAIN_MENU_STATE::IN_GAMES_MENU;
        } else if (selectedOption_ == 1) {
            currentState_ = MAIN_MENU_STATE::IN_SETTINGS;
        } else if (selectedOption_ == 2) {
            currentState_ = MAIN_MENU_STATE::IN_ABOUT;
        }
    }
}

void MainMenu::processAboutMenuState() {
    this->drawAboutMenu();
    if (InputEngine::wasButtonPressed(InputEngine::BUTTONS.at(MAIN_MENU_BUTTONS::BUTTON_ENTER))) {
        currentState_ = MAIN_MENU_STATE::IN_ROOT;
    }
}

void MainMenu::drawRootMenu() const {
    const uint16_t initialY = Font16.Height + 5;
    const uint16_t initialOptionsY = initialY * 3;

    this->display_.clear(BLACK);

    const uint16_t titleWidth = strlen(ROOT_TITLE) * Font16.Width;
    uint16_t x = (display::WIDTH - titleWidth) / 2;
    display_.drawString(x, initialY, ROOT_TITLE, Font16, BLACK, WHITE);

    for (std::size_t i = 0; i < options_.size(); ++i) {
        constexpr uint8_t optionOffset = 20;

        const uint16_t text_width = static_cast<uint16_t>(strlen(options_[i])) * Font12.Width;
        x = (display::WIDTH - text_width) / 2;
        const uint16_t y = initialOptionsY + static_cast<uint16_t>(i) * optionOffset;

        if (i == selectedOption_) {
            display_.drawString(x, y, options_[i], Font12, BLUE, WHITE);
        } else {
            display_.drawString(x, y, options_[i], Font12, BLACK, WHITE);
        }
    }
}

void MainMenu::drawAboutMenu() const {
    constexpr uint16_t titleY = 5;
    constexpr uint16_t lineSpacing = 14;

    display_.clear(BLACK);

    // title
    uint16_t textWidth = strlen(ABOUT_TITLE) * Font12.Width;
    uint16_t x = (display::WIDTH - textWidth) / 2;

    display_.drawString(
        x, titleY,
        ABOUT_TITLE,
        Font12,
        BLUE,
        WHITE
    );

    // Project name
    textWidth = strlen(ROOT_TITLE) * Font8.Width;
    x = (display::WIDTH - textWidth) / 2;

    display_.drawString(
        x, titleY + lineSpacing * 2,
        ROOT_TITLE,
        Font8,
        BLACK,
        WHITE
    );

    // Version
    textWidth = strlen(VERSION) * Font8.Width;
    x = (display::WIDTH - textWidth) / 2;

    display_.drawString(
        x, titleY + lineSpacing * 3,
        VERSION,
        Font8,
        BLACK,
        WHITE
    );

    // GitHub
    textWidth = strlen(GITHUB) * Font8.Width;
    x = (display::WIDTH - textWidth) / 2;

    display_.drawString(
        x, titleY + lineSpacing * 5,
        GITHUB,
        Font8,
        BLACK,
        WHITE
    );

    // Copyright
    textWidth = strlen(COPYRIGHT_LINE1) * Font8.Width;
    x = (display::WIDTH - textWidth) / 2;

    display_.drawString(
        x, titleY + lineSpacing * 6,
        COPYRIGHT_LINE1,
        Font8,
        BLACK,
        WHITE
    );

    textWidth = strlen(COPYRIGHT_LINE2) * Font8.Width;
    x = (display::WIDTH - textWidth) / 2;

    display_.drawString(
        x, titleY + lineSpacing * 7,
        COPYRIGHT_LINE2,
        Font8,
        BLACK,
        WHITE
    );
}
