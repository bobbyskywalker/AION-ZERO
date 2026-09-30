#ifndef AION_ZERO_FMW_ENEMY_HPP
#define AION_ZERO_FMW_ENEMY_HPP

#include <cstdint>

#include "enemy_animator.hpp"
#include "enemy_state.hpp"
#include "../base_entity.hpp"
#include "enemy_assets.hpp"

class Enemy : public BaseEntity {
private:

    EnemyAnimator animator_;
    EnemyState currentState_;
    bool damagePossible_ = false;
    bool givenDamageInFrame_ = false;

    [[nodiscard]] bool isInCameraView() const;
    static constexpr uint8_t STEP_SIZE = TILE_SQ_SIZE / 8;

    static constexpr uint16_t MAX_HEALTH = 100;

    void switchState(EnemyState state);

public:
    explicit Enemy(
        uint16_t initialX,
        uint16_t initialY,
        uint16_t initialHealth,
        BaseMap & map
    );

    void draw() override;
    void followPlayer(uint16_t playerPosX);
    void animationEndedForCurrentStateEvent(EnemyState state);

    void setCurrentState(const EnemyState state) {this->currentState_ = state;}
    [[nodiscard]] bool isDamagePossible() const {return this->damagePossible_;}
    void setDamagePossible(const bool canGiveDamage) {this->damagePossible_ = canGiveDamage;}
    [[nodiscard]] bool isGivenDamageInFrame() const {return this->givenDamageInFrame_;}
    void setGivenDamageInFrame(const bool canGiveDamage) {this->givenDamageInFrame_ = canGiveDamage;}

    static constexpr uint16_t ENEMY_DAMAGE = 10;

};


#endif //AION_ZERO_FMW_ENEMY_HPP