#include "player.hpp"

#include "../maps/lvl_1.hpp"

Player::Player(const uint16_t initialX, const uint16_t initialY)
    : animator_(*this), posX_(initialX), posY_(initialY), currentState_(PlayerState::IDLE) {}

void Player::draw() {
    animator_.drawNextFrameForCurrentState(currentState_);
}

void Player::moveHorizontally(const bool left) {
    posX_ = this->posX_ - (left ? STEP_SIZE : static_cast<uint16_t>(-STEP_SIZE));
}

void Player::startJump() {
    if (currentState_ != PlayerState::JUMPING && currentState_ != PlayerState::FALLING) {
        jumpFrom_ = posY_;
        this->switchState(PlayerState::JUMPING);
    }
}

void Player::updateJump() {
    if (currentState_ == PlayerState::JUMPING) {
        posY_ -= JUMP_STEP_SIZE;
        if (jumpFrom_ - posY_ >= JUMP_HEIGHT) {
            this->switchState(PlayerState::FALLING);
        }
    }
    else if (currentState_ == PlayerState::FALLING) {
        posY_ += JUMP_STEP_SIZE;
        if (posY_ >= jumpFrom_) {
            posY_ = jumpFrom_;
            this->switchState(PlayerState::IDLE);
        }
    }
}

void Player::attack() {
    if (currentState_ != PlayerState::JUMPING && currentState_ != PlayerState::FALLING) {
        this->switchState(PlayerState::ATTACKING);
    }
}

void Player::switchState(const PlayerState state) {
    this->currentState_ = state;
    this->animator_.resetFrameAndTimer();
}

void Player::animationEndedForStateEvent(const PlayerState state) {
    if (state == PlayerState::ATTACKING) {
        this->switchState(PlayerState::IDLE);
    }
}
