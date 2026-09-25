#ifndef AION_ZERO_FMW_PLAYER_ANIMATOR_HPP
#define AION_ZERO_FMW_PLAYER_ANIMATOR_HPP

#include <cstdint>

#include "player_assets.hpp"
#include "player_state.hpp"
#include "../../util/draw.hpp"
#include "../../maps/base_map.hpp"

class Player;
enum class PlayerState;

class PlayerAnimator {
private:
    static constexpr const unsigned char* IDLE_FRAMES[6] = {
        PLAYER_ASH_ASSETS::IDLE_1,
        PLAYER_ASH_ASSETS::IDLE_2,
        PLAYER_ASH_ASSETS::IDLE_3,
        PLAYER_ASH_ASSETS::IDLE_4,
        PLAYER_ASH_ASSETS::IDLE_5,
        PLAYER_ASH_ASSETS::IDLE_6
    };
    static constexpr uint8_t IDLE_FPS = 15;

    static constexpr const unsigned char* ATTACK_FRAMES[9] = {
        PLAYER_ASH_ASSETS::ATTACK_1,
        PLAYER_ASH_ASSETS::ATTACK_2,
        PLAYER_ASH_ASSETS::ATTACK_3,
        PLAYER_ASH_ASSETS::ATTACK_4,
        PLAYER_ASH_ASSETS::ATTACK_5,
        PLAYER_ASH_ASSETS::ATTACK_6,
        PLAYER_ASH_ASSETS::ATTACK_7,
        PLAYER_ASH_ASSETS::ATTACK_8,
        PLAYER_ASH_ASSETS::ATTACK_9
    };
    static constexpr uint8_t ATTACK_FPS = 2;

    uint8_t frameTimer_ = 0;
    uint8_t currentFrame_ = 0;

    Player & player_;

    template<size_t N>
    void updateFrameAndTimer(const unsigned char* const (&frames)[N], uint8_t fps);

public:
    explicit PlayerAnimator(Player & p);

    void drawNextFrameForCurrentState(PlayerState state);
    void resetFrameAndTimer();
};


#endif //AION_ZERO_FMW_PLAYER_ANIMATOR_HPP