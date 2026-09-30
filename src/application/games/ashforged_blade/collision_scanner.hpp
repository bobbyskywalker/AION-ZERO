#ifndef AION_ZERO_FMW_COLLISION_SCANNER_HPP
#define AION_ZERO_FMW_COLLISION_SCANNER_HPP

#include <queue>

#include "entity/base_entity.hpp"
#include "entity/enemy/enemy.hpp"

#include <memory>

#include "entity/player/player.hpp"

class CollisionScanner {
public:

    struct CollisionEvent {
        Player & target;
        Enemy & hitWith;

        CollisionEvent(Player & target, Enemy & against) : target(target), hitWith(against) {}
    };

    static void scanForEntityCollisions(
        std::queue<CollisionEvent> & collisionEventQueue,
        Player & target,
        const std::vector<std::unique_ptr<Enemy>>& checkingAgainst
    );

private:

    static bool isCollision(uint16_t aPosX, uint16_t aPosY, uint16_t bPosX, uint16_t bPosY);
};


#endif //AION_ZERO_FMW_COLLISION_SCANNER_HPP