#ifndef AION_ZERO_FMW_PLAYER_ANIMATOR_HPP
#define AION_ZERO_FMW_PLAYER_ANIMATOR_HPP

#include <cstdint>

#include "player_assets.hpp"
#include "player_state.hpp"
#include "../util/draw.hpp"
#include "../maps/base_map.hpp"

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
    static constexpr uint8_t IDLE_FPS = 4;


    uint8_t frameTimer_ = 0;
    uint8_t currentFrame_ = 0;

    Player & player_;

public:
    explicit PlayerAnimator(Player & p);

    void drawNextFrameForCurrentState(PlayerState state);
    void resetFrameAndTimer();
};


#endif //AION_ZERO_FMW_PLAYER_ANIMATOR_HPP