#ifndef AION_ZERO_FMW_PLAYER_HPP
#define AION_ZERO_FMW_PLAYER_HPP

#include <cstdint>

#include "../base_entity.hpp"
#include "player_animator.hpp"
#include "player_state.hpp"

class Player : public BaseEntity {
private:
    PlayerAnimator animator_;

    uint16_t score_{};

    uint16_t jumpFrom_{};

    uint8_t currentAttackFrame{};
    uint8_t attackFPS{8};
    uint8_t attackLatch_{0};

    PlayerState currentState_;

    static constexpr uint16_t STEP_SIZE {TILE_SQ_SIZE / 2};
    static constexpr uint16_t JUMP_STEP_SIZE {TILE_SQ_SIZE / 4};
    static constexpr uint16_t JUMP_HEIGHT {TILE_SQ_SIZE * 4};

    void switchState(PlayerState state);
    bool isPlayerOnWalkableTile();

public:
    explicit Player(uint16_t initialX, uint16_t initialY, uint16_t initialHealth, BaseMap & map);

    [[nodiscard]] bool canGiveDamageInFrame() const;

    void draw() override;

    void moveHorizontally(bool left, uint16_t mapWidth) ;
    void startJump();
    void updateJump();
    void updateAttack();
    void attack();
    void heal(uint16_t healVal);

    void updateScore(uint16_t val);
    [[nodiscard]] uint16_t getScore() const {return this->score_;}

    void animationEndedForStateEvent(PlayerState state);

    static constexpr uint16_t START_HEALTH{100};
    static constexpr uint16_t PLAYER_DAMAGE{25};
};

#endif //AION_ZERO_FMW_PLAYER_HPP