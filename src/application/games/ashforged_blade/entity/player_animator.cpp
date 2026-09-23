#include "player_animator.hpp"
#include "player.hpp"

#include <bits/range_access.h>

PlayerAnimator::PlayerAnimator(Player &p) : player_(p) {}

void PlayerAnimator::drawNextFrameForCurrentState(const PlayerState state) {
    const uint16_t screenX = this->player_.getPosX() - this->player_.getCameraPosX();

    if (state == PlayerState::IDLE || state == PlayerState::JUMPING || state == PlayerState::FALLING) {
        updateFrameAndTimer(IDLE_FRAMES, IDLE_FPS);
        drawSprite(
            IDLE_FRAMES[currentFrame_], screenX, player_.getPosY(), PLAYER_SQ_SIZE, PLAYER_SQ_SIZE
        );
    } else if (state == PlayerState::ATTACKING) {
        updateFrameAndTimer(ATTACK_FRAMES, ATTACK_FPS);
        drawSprite(
            ATTACK_FRAMES[currentFrame_], screenX, player_.getPosY(), PLAYER_SQ_SIZE, PLAYER_SQ_SIZE
        );
        if (currentFrame_ == std::size(ATTACK_FRAMES) - 1) {
            this->player_.animationEndedForStateEvent(PlayerState::ATTACKING);
        }
    }
}

template<size_t N>
void PlayerAnimator::updateFrameAndTimer(const unsigned char* const (&frames)[N], const uint8_t fps) {
    if (++this->frameTimer_ >= fps) {
        this->frameTimer_ = 0;
        this->currentFrame_ = (this->currentFrame_ + 1) % std::size(frames);
    }
}

// to be called on every player state change
void PlayerAnimator::resetFrameAndTimer() {
    this->currentFrame_ = 0;
    this->frameTimer_ = 0;
}
