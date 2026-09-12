#include "Module_ASH.hpp"

Module_ASH::Module_ASH(display::LcdDisplay& display) : Module(display), game_(Game_ASH{}) {}

[[nodiscard]] ModuleSwitchRequest Module_ASH::loop() {
    while (true) {
        const ModuleSwitchRequest event = this->game_.runGame();
        return event;
    }
}
