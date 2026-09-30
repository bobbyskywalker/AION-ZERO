#ifndef AION_ZERO_FMW_ENEMY_ANIMATOR_HPP
#define AION_ZERO_FMW_ENEMY_ANIMATOR_HPP

class EnemyAnimator : public EntityAnimator {
private:
    static constexpr unsigned char* FOLLOWING_FRAMES[5] = {

    };
    static constexpr uint8_t FOLLOWING_FPS = 3; // tbd


    static constexpr const unsigned char *ATTACK_FRAMES[5] = {

    };
    static constexpr ATTACK_FPS = 3; //tbd


    uint8_t frameTimer_ = 0;
    uint8_t currentFrame = 0;

    Enemy & enemy;
};

#endif //AION_ZERO_FMW_ENEMY_ANIMATOR_HPP