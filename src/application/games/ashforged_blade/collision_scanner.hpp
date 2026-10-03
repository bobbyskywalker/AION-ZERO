#ifndef AION_ZERO_FMW_COLLISION_SCANNER_HPP
#define AION_ZERO_FMW_COLLISION_SCANNER_HPP

#include <queue>

#include "entity/base_entity.hpp"
#include "entity/enemy/enemy.hpp"

#include <memory>
#include <variant>

#include "entity/player/player.hpp"

class CollisionScanner {
public:

    struct PlayerCollisionEvent {
        Player& target;
        Enemy& hitWith;
        PlayerCollisionEvent(Player& target, Enemy& hitWith): target(target), hitWith(hitWith) {}
    };

    struct EnemyCollisionEvent {
        Enemy& e1;
        Enemy& e2;
        EnemyCollisionEvent(Enemy& e1, Enemy& e2): e1(e1), e2(e2) {}
    };

    using CollisionEvent = std::variant<PlayerCollisionEvent,EnemyCollisionEvent>;

    template <typename Container>
    static void scanForAllCollisions(std::queue<CollisionEvent>& collisionEventQueue, Player & p, const Container & enemies);

private:
    static bool isCollision(uint16_t aPosX, uint16_t aPosY, uint16_t bPosX, uint16_t bPosY);

    static void scanForEntityCollisionsWith(
        std::queue<CollisionEvent> & collisionEventQueue,
        Player & target,
        const std::vector<std::unique_ptr<Enemy>>& checkingAgainst
    );

    template <typename Container>
    static void scanForEntityCollisionsIn(std::queue<CollisionEvent>& collisionEventQueue, const Container& enemies);

};

template <typename Container>
void CollisionScanner::scanForAllCollisions(
    std::queue<CollisionEvent>& collisionEventQueue,
    Player & p,
    const Container& enemies
) {
    scanForEntityCollisionsWith(collisionEventQueue, p, enemies);
    scanForEntityCollisionsIn(collisionEventQueue, enemies);
}

template <typename Container>
void CollisionScanner::scanForEntityCollisionsIn(
    std::queue<CollisionEvent>& collisionEventQueue,
    const Container& enemies
) {
    for (auto it = enemies.begin(); it != enemies.end(); ++it) {
        auto next = std::next(it);

        for (; next != enemies.end(); ++next) {
            Enemy& a = **it;

            if (Enemy& b = **next;
                isCollision(a.getPosX(),a.getPosY(),b.getPosX(),b.getPosY()))
            {
                collisionEventQueue.emplace(std::in_place_type<EnemyCollisionEvent>, a, b);
            }
        }
    }
}

inline void CollisionScanner::scanForEntityCollisionsWith(
    std::queue<CollisionEvent> & collisionEventQueue,
    Player & target,
    const std::vector<std::unique_ptr<Enemy>>& checkingAgainst)
{
    for (auto & e : checkingAgainst) {
        if (isCollision(target.getPosX(), target.getPosY(), e->getPosX(), e->getPosY())) {
            collisionEventQueue.emplace(std::in_place_type<PlayerCollisionEvent>, target, *e);
        }
    }
}

inline bool CollisionScanner::isCollision(
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

#endif //AION_ZERO_FMW_COLLISION_SCANNER_HPP