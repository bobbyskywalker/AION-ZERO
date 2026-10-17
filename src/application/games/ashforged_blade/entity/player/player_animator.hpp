#ifndef AION_ZERO_FMW_PLAYER_ANIMATOR_HPP
#define AION_ZERO_FMW_PLAYER_ANIMATOR_HPP

#include <cstdint>

#include "player_assets.hpp"
#include "player_state.hpp"
#include "../entity_animator.hpp"
#include "../../util/draw.hpp"
#include "../../maps/base_map.hpp"

class Player;
enum class PlayerState;

class PlayerAnimator : public EntityAnimator {
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

    static constexpr uint8_t ATTACK_FPS = 2;
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

    Player & player_;

public:
    explicit PlayerAnimator(Player & p);

    void drawNextFrameForCurrentState(PlayerState state);

    static constexpr uint8_t ATTACK_FRAMES_LEN = 9;
};


#endif //AION_ZERO_FMW_PLAYER_ANIMATOR_HPP