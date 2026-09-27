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
        drawHealthBar(this->health_, MAX_HEALTH);

        drawSprite(
            ENEMY_ASH_ASSETS::ASHIGARU_ENEMY_1,
            screenX,
            this->posY_,
            ENTITY_SQ_SIZE,
            ENTITY_SQ_SIZE
        );
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
