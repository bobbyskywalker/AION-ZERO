#ifndef AION_ZERO_FMW_MAIN_MENU_HPP
#define AION_ZERO_FMW_MAIN_MENU_HPP

#include "../module.hpp"
#include <array>

constexpr auto TITLE = "AION ZERO";

class MainMenu : public Module {
private:
    static constexpr std::array<const char*, 3> options = {"Games","Settings","About"};
public:
    explicit MainMenu(display::LcdDisplay& display) : Module(display) {}
    [[nodiscard]] ModuleSwitchRequest loop() override;
    void onEnter() override;
};

#endif //AION_ZERO_FMW_MAIN_MENU_HPP