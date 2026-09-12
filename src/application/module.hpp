#ifndef AION_ZERO_FMW_MODULE_HPP
#define AION_ZERO_FMW_MODULE_HPP

#include "../display/display.hpp"

// all the module implementations ought to be registered here
enum class ModuleSwitchRequest {
    MainMenu,
    AshforgedBlade
};

class Module {
protected:
    display::LcdDisplay& display_;
public:
    explicit Module(display::LcdDisplay& display) : display_(display) {}
    virtual ~Module() = default;

    virtual ModuleSwitchRequest loop() = 0;
};

#endif //AION_ZERO_FMW_MODULE_HPP