#ifndef AION_ZERO_FMW_MENU_ASH_HPP
#define AION_ZERO_FMW_MENU_ASH_HPP

#include <cstdint>

#include "../../../../display/display.hpp"

enum class MENU_ASH_OPTIONS {
    PLAY,
    EXIT
};

class Menu_ASH {
private:

    void showTutorial();
    void draw([[maybe_unused]] display::LcdDisplay & display) const;

    uint8_t currentOption_{0};

public:
    Menu_ASH() = default;

    void runMenu(display::LcdDisplay & display);
    void updateOption(uint8_t dir /* 0 up, 1 down */);

    static constexpr MENU_ASH_OPTIONS menuOptions_[] = {MENU_ASH_OPTIONS::PLAY, MENU_ASH_OPTIONS::EXIT};
    [[nodiscard]] uint8_t getSelectedOption() const {return this->currentOption_;};

};


#endif //AION_ZERO_FMW_MENU_ASH_HPP