#ifndef AION_ZERO_FMW_PLAYER_HPP
#define AION_ZERO_FMW_PLAYER_HPP

#include <cstdint>

#include "player_assets.hpp"
#include "../maps/lvl_1.hpp"

enum class PlayerState {
    IDLE,
    WALKING,
    JUMPING,
    FALLING,
    ATTACKING
};

class Player {
private:
    uint16_t posX_;
    uint16_t posY_;
    uint16_t jumpFrom_{};
    PlayerState currentState_;

    static constexpr uint16_t STEP_SIZE = TILE_SQ_SIZE / 2;
    static constexpr uint16_t JUMP_STEP_SIZE = TILE_SQ_SIZE / 4;
    static constexpr uint16_t JUMP_HEIGHT = TILE_SQ_SIZE * 3;

public:
    explicit Player(uint16_t initialX, uint16_t initialY);

    [[nodiscard]] uint16_t getPosX() const { return posX_; }
    [[nodiscard]] uint16_t getPosY() const { return posY_; }
    void setPosX(const uint16_t pos) { this->posX_ = pos; }
    void setPosY(const uint16_t pos) { this->posY_ = pos; }
    PlayerState getCurrentState();

    void moveHorizontally(bool left);
    void startJump();
    void updateJump();
};

#endif //AION_ZERO_FMW_PLAYER_HPP