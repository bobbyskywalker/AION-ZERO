#include "input.hpp"

#include <hardware/gpio.h>
#include <hardware/timer.h>

void InputEngine::registerButtons() {
    for (auto const& pin : BUTTONS) {
        gpio_init(pin);
        gpio_set_dir(pin, GPIO_IN);
        gpio_pull_up(pin);
    }
}

InputEngine::ButtonState getButtonState(const uint8_t& pin) {
    if (!gpio_get(pin)) {
        return InputEngine::ButtonState::PRESSED;
    }
    return InputEngine::ButtonState::RELEASED;
}

bool InputEngine::wasButtonPressed(const uint8_t& pin) {
    static std::array<ButtonTracker, BUTTONS.size()> trackers{};

    return trackers[pin].wasPressed(
        !gpio_get(pin),
        time_us_64()
    );
}