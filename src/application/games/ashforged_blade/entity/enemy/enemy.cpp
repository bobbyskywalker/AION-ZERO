#include "enemy.hpp"

Enemy::Enemy(
    const uint16_t initialX,
    const uint16_t initialY,
    const uint16_t initialHealth,
    BaseMap &map
) : BaseEntity(initialX, initialY, initialHealth, map) {
}

void Enemy::draw() {
    const auto screenX = posX_ - getCameraPosX();

    if (isInCameraView()) {
        drawRectangle(
            screenX,
            posY_ - ENTITY_SQ_SIZE,
            screenX + ENTITY_SQ_SIZE,
            posY_,
            RED
        );
    }
}

void Enemy::followPlayer(const uint16_t playerPosX) {
    if (isInCameraView()) {
        if (playerPosX < this->posX_) {
            posX_ -= STEP_SIZE;
        }
        if (playerPosX > this->posX_) {
            posX_ += STEP_SIZE;
        }
    }
}

[[nodiscard]] bool Enemy::isInCameraView() const {
    const auto enemyTileX = getTilePosX();
    const auto cameraTileX = getCameraPosX() / TILE_SQ_SIZE;
    return enemyTileX >= cameraTileX && enemyTileX < cameraTileX + BaseMap::CAMERA_SIZE;
}
