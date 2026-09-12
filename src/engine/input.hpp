#ifndef AION_ZERO_FMW_INPUT_HPP
#define AION_ZERO_FMW_INPUT_HPP

#include <cstdint>
#include <array>

namespace InputEngine {

    struct ButtonTracker {
        bool stableState = false;
        bool lastReading = false;
        uint64_t lastChangeUs = 0;

        bool wasPressed(const bool reading, const uint64_t nowUs) {
            if (reading != lastReading) {
                lastReading = reading;
                lastChangeUs = nowUs;
            }

            if (nowUs - lastChangeUs >= 20'000) {
                if (stableState != lastReading) {
                    const bool pressed = lastReading && !stableState;
                    stableState = lastReading;
                    return pressed;
                }
            }
            return false;
        }

    };

    constexpr std::array<std::uint8_t, 4> BUTTONS = {15, 17, 2, 3};

    enum class ButtonState {
        PRESSED,
        RELEASED
    };

    void            registerButtons();
    ButtonState     getButtonState(const uint8_t& pin);
    bool            wasButtonPressed(const uint8_t& pin);

}
#endif //AION_ZERO_FMW_INPUT_HPP