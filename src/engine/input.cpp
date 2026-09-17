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

InputEngine::ButtonState InputEngine::getButtonState(const uint8_t& pin) {
    if (!gpio_get(pin)) {
        return ButtonState::PRESSED;
    }
    return ButtonState::RELEASED;
}

/* prevents constant input on hold */
bool InputEngine::wasButtonPressed(const uint8_t& pin) {
    static std::array<ButtonTracker, BUTTONS.size()> trackers{};

    return trackers[pin].wasPressed(
        !gpio_get(pin),
        time_us_64()
    );
}

/* event emitting helper, takes a consumer-pointer to write events to */
void InputEngine::inputListener(std::queue<ButtonEvent> &eventQueue) {
    for (auto const& pin : BUTTONS) {
        if (!gpio_get(pin)) {
            eventQueue.push(ButtonEvent{getButtonState(pin), pin});
        }
    }
}
