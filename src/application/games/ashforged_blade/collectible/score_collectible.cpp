#include "score_collectible.hpp"

#include "collectible_assets.hpp"
#include "../maps/base_map.hpp"
#include "../util/draw.hpp"

ScoreCollectible::ScoreCollectible(const uint16_t initialX, const uint16_t initialY)
    : BaseCollectible(initialX, initialY) {}

void ScoreCollectible::draw() const {
    const uint16_t screenX = this->getPosX() - this->getCameraPosX();

    drawSprite(
        CollectibleAssets::SCORE_COLLECTIBLE,
        screenX,
        this->posY_,
        ENTITY_SQ_SIZE,
        ENTITY_SQ_SIZE
    );
}
