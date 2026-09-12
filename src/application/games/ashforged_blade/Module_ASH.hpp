#ifndef AION_ZERO_FMW_ENGINE_ASH_HPP
#define AION_ZERO_FMW_ENGINE_ASH_HPP

#include "Game_ASH.hpp"
#include "../../module.hpp"

enum class Module_ASH_State {
    MENU,
    IN_GAME
};

class Module_ASH : public Module {
private:
    Game_ASH game_;

public:
    explicit Module_ASH(display::LcdDisplay& display);
    [[nodiscard]] ModuleSwitchRequest loop() override;
};

#endif //AION_ZERO_FMW_ENGINE_ASH_HPP