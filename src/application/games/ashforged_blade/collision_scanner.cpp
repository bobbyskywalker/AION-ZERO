#include "collision_scanner.hpp"

void CollisionScanner::scanForEntityCollisions(
    std::queue<CollisionEvent> & collisionEventQueue,
    BaseEntity & target,
    const std::vector<std::unique_ptr<Enemy>>& checkingAgainst)
{
    for (auto & e : checkingAgainst) {
        if (isCollision(target.getPosX(), target.getPosY(), e->getPosX(), e->getPosY())) {
            collisionEventQueue.emplace(target, *e);
        }
    }
}

bool CollisionScanner::isCollision(
    const uint16_t aPosX,
    const uint16_t aPosY,
    const uint16_t bPosX,
    const uint16_t bPosY
) {
    return aPosX < bPosX + ENTITY_SQ_SIZE &&
            aPosX + ENTITY_SQ_SIZE > bPosX &&
                aPosY < bPosY + ENTITY_SQ_SIZE &&
                    aPosY + ENTITY_SQ_SIZE > bPosY;
}
