#ifndef AION_ZERO_FMW_ENEMY_ANIMATOR_HPP
#define AION_ZERO_FMW_ENEMY_ANIMATOR_HPP

#include "enemy_assets.hpp"
#include "../entity_animator.hpp"

class Enemy;
enum class EnemyState;

class EnemyAnimator : public EntityAnimator {
private:

    static constexpr const unsigned char *FOLLOWING_FRAMES[1] {
        ENEMY_ASH_ASSETS::ASHIGARU_IDLE_1,
    };

    static constexpr const unsigned char *ATTACK_FRAMES[5] = {
        ENEMY_ASH_ASSETS::ASHIGARU_ATTACK_1,
        ENEMY_ASH_ASSETS::ASHIGARU_ATTACK_2,
        ENEMY_ASH_ASSETS::ASHIGARU_ATTACK_3,
        ENEMY_ASH_ASSETS::ASHIGARU_ATTACK_4,
        ENEMY_ASH_ASSETS::ASHIGARU_ATTACK_5
    };

    // shitty mechanic but could not think of anything better
    // enemy takes damage on 4 animation sprite, gives the player some time for escape :)
    static constexpr uint8_t DAMAGE_WINDOW_START_IDX = 3;
    static constexpr uint8_t ATTACK_FPS = 6; //tbd

    Enemy & enemy_;

public:
    explicit EnemyAnimator(Enemy & e);

    void drawNextFrameForCurrentState(EnemyState state);

};

#endif //AION_ZERO_FMW_ENEMY_ANIMATOR_HPP