#include "player_animator.hpp"
#include "player.hpp"

#include <bits/range_access.h>

PlayerAnimator::PlayerAnimator(Player &p) : EntityAnimator(), player_(p) {}

void PlayerAnimator::drawNextFrameForCurrentState(const PlayerState state) {
    const uint16_t screenX = this->player_.getPosX() - this->player_.getCameraPosX();

    if (state == PlayerState::IDLE || state == PlayerState::JUMPING || state == PlayerState::FALLING) {
        this->updateFrameAndTimer(IDLE_FRAMES, IDLE_FPS);
        drawSprite(
            IDLE_FRAMES[currentFrame_], screenX, player_.getPosY(), ENTITY_SQ_SIZE, ENTITY_SQ_SIZE
        );
    } else if (state == PlayerState::ATTACKING) {
        this->updateFrameAndTimer(ATTACK_FRAMES, ATTACK_FPS);
        drawSprite(
            ATTACK_FRAMES[currentFrame_], screenX, player_.getPosY(), ENTITY_SQ_SIZE, ENTITY_SQ_SIZE
        );
        if (currentFrame_ == std::size(ATTACK_FRAMES) - 1) {
            this->player_.animationEndedForStateEvent(PlayerState::ATTACKING);
        }
    }
}
