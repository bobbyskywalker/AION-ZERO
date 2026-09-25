#include "player.hpp"

#include "../../maps/lvl_1.hpp"

Player::Player(const uint16_t initialX, const uint16_t initialY, BaseMap & map)
    : BaseEntity(initialX, initialY, map), animator_(*this), currentState_(PlayerState::IDLE)
{}

void Player::draw() {
    animator_.drawNextFrameForCurrentState(currentState_);
}

void Player::moveHorizontally(const bool left, const uint16_t mapWidth) {
    if (left) {
        if (this->posX_ >= STEP_SIZE) {
            this->posX_ -= STEP_SIZE;
        } else {
            this->posX_ = 0;
        }
    } else {
        if (this->posX_ + STEP_SIZE < mapWidth * TILE_SQ_SIZE) {
            this->posX_ += STEP_SIZE;
        } else {
            this->posX_ = mapWidth * TILE_SQ_SIZE - STEP_SIZE;
        }
    }
    if (!this->map_.isWalkableTileOnPos(this->getTilePosX(), this->getTilePosY())
            && this->currentState_ != PlayerState::FALLING) {
        switchState(PlayerState::FALLING);
    }
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

        const uint16_t tileX = this->getTilePosX();
        const uint16_t tileY = this->getTilePosY();

        if (this->map_.isWalkableTileOnPos(tileX, tileY + PLAYER_TO_WALKABLE_TILE_OFFSET)) {
            posY_ = tileY * TILE_SQ_SIZE;
            this->switchState(PlayerState::IDLE);
        } else if (this->map_.isGroundOnPos(tileY)) {
            posY_ = INITIAL_PLAYER_TILE_Y * TILE_SQ_SIZE;
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
