#ifndef AION_ZERO_FMW_COLLISION_SCANNER_HPP
#define AION_ZERO_FMW_COLLISION_SCANNER_HPP

#include <queue>

#include "entity/base_entity.hpp"
#include "entity/enemy/enemy.hpp"

#include <memory>
#include <variant>

#include "collectible/base_collectible.hpp"
#include "entity/player/player.hpp"

class ScoreCollectible;
class HealthCollectible;

class CollisionScanner {
public:
    struct PlayerCollisionEvent {
        Player &target;
        Enemy &hitWith;

        PlayerCollisionEvent(Player &target, Enemy &hitWith) : target(target), hitWith(hitWith) {
        }
    };

    struct EnemyCollisionEvent {
        Enemy &e1;
        Enemy &e2;

        EnemyCollisionEvent(Enemy &e1, Enemy &e2) : e1(e1), e2(e2) {
        }
    };

    struct CollectibleCollisionEvent {
        Player &target;
        BaseCollectible &collectible;

        CollectibleCollisionEvent(Player &player, BaseCollectible &collectible) : target(player),
            collectible(collectible) {
        }
    };

    using CollisionEvent = std::variant<PlayerCollisionEvent, EnemyCollisionEvent, CollectibleCollisionEvent>;

    template<typename EnemyContainer, typename CollectibleContainer>
    static void scanForAllCollisions(
        std::queue<CollisionEvent> &collisionEventQueue,
        Player &p,
        const EnemyContainer &enemies,
        const CollectibleContainer &collectibles
    );

private:
    static bool isCollision(uint16_t aPosX, uint16_t aPosY, uint16_t bPosX, uint16_t bPosY);

    template<typename T>
    static void scanForEntityCollisionsWith(
        std::queue<CollisionEvent> &collisionEventQueue,
        Player &target,
        const std::vector<T> &checkingAgainst
    );

    template<typename Container>
    static void scanForEntityCollisionsIn(std::queue<CollisionEvent> &collisionEventQueue, const Container &enemies);
};

template<typename T>
void CollisionScanner::scanForEntityCollisionsWith(
    std::queue<CollisionEvent> &collisionEventQueue,
    Player &target,
    const std::vector<T> &checkingAgainst
) {
    using CollectibleVariant =
            std::variant<HealthCollectible, ScoreCollectible>;

    static_assert(
        std::is_same_v<T, std::unique_ptr<Enemy> > ||
        std::is_same_v<T, CollectibleVariant>,
        "Unsupported entity type passed to scanForEntityCollisionsWith"
    );

    for (const auto &e: checkingAgainst) {
        if constexpr (std::is_same_v<T, std::unique_ptr<Enemy> >) {
            if (isCollision(
                target.getPosX(), target.getPosY(),
                e->getPosX(), e->getPosY()
            )) {
                collisionEventQueue.emplace(
                    std::in_place_type<PlayerCollisionEvent>,
                    target, *e
                );
            }
        } else {
            std::visit([&](const auto &collectible) {
                if (isCollision(
                    target.getPosX(), target.getPosY(),
                    collectible.getPosX(), collectible.getPosY()
                )) {
                    collisionEventQueue.emplace(
                        std::in_place_type<CollectibleCollisionEvent>,
                        target,
                        static_cast<BaseCollectible &>(
                            const_cast<std::decay_t<decltype(collectible)> &>(
                                collectible
                            )
                        )
                    );
                }
            }, e);
        }
    }
}

template<typename EnemyContainer, typename CollectibleContainer>
void CollisionScanner::scanForAllCollisions(
    std::queue<CollisionEvent> &collisionEventQueue,
    Player &p,
    const EnemyContainer &enemies,
    const CollectibleContainer &collectibles
) {
    scanForEntityCollisionsWith(collisionEventQueue, p, enemies);
    scanForEntityCollisionsWith(collisionEventQueue, p, collectibles);
    scanForEntityCollisionsIn(collisionEventQueue, enemies);
}

template<typename Container>
void CollisionScanner::scanForEntityCollisionsIn(
    std::queue<CollisionEvent> &collisionEventQueue,
    const Container &enemies
) {
    for (auto it = enemies.begin(); it != enemies.end(); ++it) {
        auto next = std::next(it);

        for (; next != enemies.end(); ++next) {
            Enemy &a = **it;

            if (Enemy &b = **next;
                isCollision(a.getPosX(), a.getPosY(), b.getPosX(), b.getPosY())) {
                collisionEventQueue.emplace(std::in_place_type<EnemyCollisionEvent>, a, b);
            }
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
