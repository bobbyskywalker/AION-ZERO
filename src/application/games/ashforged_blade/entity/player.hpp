#ifndef AION_ZERO_FMW_PLAYER_HPP
#define AION_ZERO_FMW_PLAYER_HPP

#include <cstdint>

#include "player_animator.hpp"
#include "player_state.hpp"
#include "../maps/lvl_1.hpp"

class Player {
private:
    PlayerAnimator animator_;

    uint16_t posX_;
    uint16_t posY_;
    uint16_t jumpFrom_{};
    PlayerState currentState_;

    static constexpr uint16_t STEP_SIZE = TILE_SQ_SIZE / 2;
    static constexpr uint16_t JUMP_STEP_SIZE = TILE_SQ_SIZE / 4;
    static constexpr uint16_t JUMP_HEIGHT = TILE_SQ_SIZE * 3;

    void switchState(PlayerState state);

public:
    explicit Player(uint16_t initialX, uint16_t initialY);

    [[nodiscard]] uint16_t getPosX() const { return posX_; }
    [[nodiscard]] uint16_t getPosY() const { return posY_; }
    void setPosX(const uint16_t pos) { this->posX_ = pos; }
    void setPosY(const uint16_t pos) { this->posY_ = pos; }
    PlayerState getCurrentState();

    void draw();

    void moveHorizontally(bool left);
    void startJump();
    void updateJump();
    void startAttack();
    void updateAttack();
};

#endif //AION_ZERO_FMW_PLAYER_HPP