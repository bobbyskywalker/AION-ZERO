#ifndef AION_ZERO_FMW_PLAYER_HPP
#define AION_ZERO_FMW_PLAYER_HPP

#include <cstdint>

#include "player_animator.hpp"
#include "player_state.hpp"
#include "../maps/lvl_1.hpp"

class Player {
private:
    PlayerAnimator animator_;

    BaseMap & map_;

    uint16_t posX_;
    uint16_t posY_;
    uint16_t cameraPosX_{};
    uint16_t jumpFrom_{};

    uint8_t currentAttackFrame{};
    uint8_t attackFPS = 8;

    PlayerState currentState_;

    static constexpr uint16_t STEP_SIZE = TILE_SQ_SIZE / 2;
    static constexpr uint16_t JUMP_STEP_SIZE = TILE_SQ_SIZE / 4;
    static constexpr uint16_t JUMP_HEIGHT = TILE_SQ_SIZE * 4;

    void switchState(PlayerState state);
    bool isPlayerOnWalkableTile();

public:
    explicit Player(uint16_t initialX, uint16_t initialY, BaseMap & map);

    [[nodiscard]] uint16_t getPosX() const { return posX_; }
    [[nodiscard]] uint16_t getPosY() const { return posY_; }
    [[nodiscard]] uint16_t getCameraPosX() const { return cameraPosX_; }
    [[nodiscard]] uint16_t getTilePosX() const { return posX_ / TILE_SQ_SIZE; }
    [[nodiscard]] uint16_t getTilePosY() const { return posY_ / TILE_SQ_SIZE; }
    void setPosX(const uint16_t pos) { this->posX_ = pos; }
    void setPosY(const uint16_t pos) { this->posY_ = pos; }
    void setCameraPosX(const uint16_t pos) { this->cameraPosX_ = pos; }
    PlayerState getCurrentState();

    void draw();

    void moveHorizontally(bool left, uint16_t mapWidth) ;
    void startJump();
    void updateJump();
    void attack();

    void animationEndedForStateEvent(PlayerState state);
};

#endif //AION_ZERO_FMW_PLAYER_HPP