#include "player_animator.hpp"
#include "player.hpp"

#include <bits/range_access.h>

PlayerAnimator::PlayerAnimator(Player &p) : player_(p) {}

void PlayerAnimator::drawNextFrameForCurrentState(const PlayerState state) {
    if (state == PlayerState::IDLE || state == PlayerState::JUMPING || state == PlayerState::FALLING) {
        if (++this->frameTimer_ >= IDLE_FPS) {
            this->frameTimer_ = 0;
            this->currentFrame_ = (this->currentFrame_ + 1) % std::size(IDLE_FRAMES);
        }
    }
    drawSprite(
        IDLE_FRAMES[currentFrame_], player_.getPosX(), player_.getPosY(), PLAYER_SQ_SIZE, PLAYER_SQ_SIZE
    );
}

// to be called on every player state change
void PlayerAnimator::resetFrameAndTimer() {
    this->currentFrame_ = 0;
    this->frameTimer_ = 0;
}
