#include "health_collectible.hpp"

#include "../maps/base_map.hpp"
#include "../util/draw.hpp"

HealthCollectible::HealthCollectible(const uint16_t initialX, const uint16_t initialY)
    : BaseCollectible(initialX, initialY) {}

void HealthCollectible::draw() const {
    const uint16_t screenX = this->getPosX() - this->getCameraPosX();

    drawSprite(
        CollectibleAssets::HEALTH_COLLECTIBLE,
        screenX,
        this->posY_,
        ENTITY_SQ_SIZE,
        ENTITY_SQ_SIZE
    );
}
