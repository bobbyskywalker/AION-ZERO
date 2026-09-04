#ifndef AION_ZERO_FMW_MAIN_MENU_HPP
#define AION_ZERO_FMW_MAIN_MENU_HPP

#include "../module.hpp"

class MainMenu : public Module {
private:
    const char* options[3] = {"Games", "Settings", "About"};
public:
    explicit MainMenu(display::LcdDisplay& display) : Module(display) {}
    [[noreturn]] void loop() override;
};

#endif //AION_ZERO_FMW_MAIN_MENU_HPP