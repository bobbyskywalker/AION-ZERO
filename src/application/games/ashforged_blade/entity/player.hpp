#ifndef AION_ZERO_FMW_PLAYER_HPP
#define AION_ZERO_FMW_PLAYER_HPP

#include <cstdint>

#include "player_assets.hpp"

enum class PlayerState {
    IDLE,
    WALKING,
    JUMPING,
    ATTACKING
};

class Player {
private:
    uint16_t posX_;
    uint16_t posY_;
    // PlayerState currentState_;

public:
    explicit Player(uint16_t initialX, uint16_t initialY);

    [[nodiscard]] uint16_t getPosX() const { return posX_; }
    [[nodiscard]] uint16_t getPosY() const { return posY_; }
    PlayerState getCurrentState();
};

#endif //AION_ZERO_FMW_PLAYER_HPP