#ifndef AION_ZERO_FMW_PLAYER_HPP
#define AION_ZERO_FMW_PLAYER_HPP

#include <cstdint>

#include "../base_entity.hpp"
#include "player_animator.hpp"
#include "player_state.hpp"

class Player : public BaseEntity {
private:
    PlayerAnimator animator_;

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
    explicit Player(uint16_t initialX, uint16_t initialY, uint16_t initialHealth, BaseMap & map);

    PlayerState getCurrentState();

    void draw() override;

    void moveHorizontally(bool left, uint16_t mapWidth) ;
    void startJump();
    void updateJump();
    void attack();

    void animationEndedForStateEvent(PlayerState state);

    static constexpr uint16_t START_HEALTH = 100;
};

#endif //AION_ZERO_FMW_PLAYER_HPP