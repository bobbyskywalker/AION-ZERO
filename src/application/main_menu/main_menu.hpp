#ifndef AION_ZERO_FMW_MAIN_MENU_HPP
#define AION_ZERO_FMW_MAIN_MENU_HPP

#include "../module.hpp"
#include <array>

namespace MAIN_MENU_BUTTONS {
    constexpr uint8_t BUTTON_UP = 0;
    constexpr uint8_t BUTTON_DOWN = 1;
    constexpr uint8_t BUTTON_ENTER = 2;
}

class MainMenu : public Module {
private:
    static constexpr std::array<const char*, 3> options_ = {"Games","Settings","About"};
    uint8_t selectedOption_ = 0;

    void drawRootMenu() const;
    void drawAboutMenu() const;

    void processRootMenuState();
    void processAboutMenuState();
    void processMenuState();

    enum class MAIN_MENU_STATE {
        IN_ROOT,
        IN_GAMES_MENU,
        IN_SETTINGS,
        IN_ABOUT,
    };
    MAIN_MENU_STATE currentState_ = MAIN_MENU_STATE::IN_ROOT;

public:
    explicit MainMenu(display::LcdDisplay& display) : Module(display) {}
    [[nodiscard]] ModuleSwitchRequest loop() override;
};

constexpr auto ROOT_TITLE = "AION ZERO";
constexpr auto ABOUT_TITLE = "ABOUT";
constexpr auto VERSION = "v0.0.1";
constexpr auto GITHUB = "github.com/bobbyskywalker";
constexpr auto COPYRIGHT_LINE1 = "(C) 2026";
constexpr auto COPYRIGHT_LINE2 = "Aleksander Garbacz";

#endif //AION_ZERO_FMW_MAIN_MENU_HPP
