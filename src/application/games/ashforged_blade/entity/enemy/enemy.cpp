#include "enemy.hpp"

Enemy::Enemy(
    const uint16_t initialX,
    const uint16_t initialY,
    const uint16_t initialHealth,
    BaseMap &map
) : BaseEntity(initialX, initialY, initialHealth, map),
    animator_(EnemyAnimator(*this)),
    currentState_(EnemyState::FOLLOWING) {}

void Enemy::draw() {
    if (isInCameraView()) {
        drawHealthBar(this->health_, MAX_HEALTH, MAGENTA);
        this->animator_.drawNextFrameForCurrentState(this->currentState_);
    }
}

void Enemy::followPlayer(const uint16_t playerPosX) {
    if (isInCameraView()) {
        if (playerPosX < this->posX_ + TILE_SQ_SIZE) {
            posX_ -= STEP_SIZE;
        }
        if (playerPosX > this->posX_ - TILE_SQ_SIZE) {
            posX_ += STEP_SIZE;
        }
    }
}

[[nodiscard]] bool Enemy::isInCameraView() const {
    const auto enemyTileX = getTilePosX();
    const auto cameraTileX = getCameraPosX() / TILE_SQ_SIZE;
    return enemyTileX >= cameraTileX && enemyTileX < cameraTileX + BaseMap::CAMERA_SIZE;
}

void Enemy::switchState(const EnemyState state) {
    this->damagePossible_ = false;
    this->currentState_ = state;
    this->givenDamageInFrame_ = false;
    this->animator_.resetFrameAndTimer();
}

void Enemy::animationEndedForCurrentStateEvent(const EnemyState state) {
    if (state == EnemyState::ATTACKING) {
        this->switchState(EnemyState::FOLLOWING);
    }
}