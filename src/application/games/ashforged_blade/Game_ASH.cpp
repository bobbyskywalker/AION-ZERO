#include "Game_ASH.hpp"

#include "Module_ASH.hpp"
#include "../../../engine/input.hpp"
#include <algorithm>
#include <variant>

#include "collectible/health_collectible.hpp"
#include "entity/enemy/enemy_state.hpp"

Game_ASH::Game_ASH(display::LcdDisplay &display) : currentState_(Game_ASH_State::GAMEPLAY), display_(display) {
    this->eventQueue_ = std::make_unique<std::queue<InputEngine::ButtonEvent> >();
    this->collisionEventQueue_ = std::make_unique<std::queue<CollisionScanner::CollisionEvent> >();
    this->gameMap_ = std::make_unique<MapLVL1>();
    this->player_ = std::make_unique<Player>(
        INITIAL_PLAYER_TILE_X * TILE_SQ_SIZE,
        INITIAL_PLAYER_TILE_Y * TILE_SQ_SIZE, Player::START_HEALTH,
        this->gameMap_.get()
    );
    spawnEnemies();
    spawnCollectibles();
}

void Game_ASH::spawnEnemies() {
    const auto enemyCoords = BaseMap::provideTypeCoordinates(
        this->gameMap_->getMap(), MapDescription::TILE_ID::ENEMY_POS_ID
    );
    enemies_.reserve(enemyCoords.size());
    for (auto [x, y]: enemyCoords) {
        enemies_.emplace_back(
            std::make_unique<Enemy>(x * TILE_SQ_SIZE, y * TILE_SQ_SIZE, 100, *this->gameMap_)
        );
    }
}

void Game_ASH::spawnCollectibles() {
    const auto fetchCollectibleCoords =
            [](const std::array<std::array<uint8_t, MAP_WIDTH>, MAP_HEIGHT> &map, const MapDescription::TILE_ID id) {
        return BaseMap::provideTypeCoordinates(map, id);
    };
    const auto emplaceCollectiblesForType =
            [this](auto factory, const std::vector<std::pair<uint8_t, uint8_t> > &coords) {
        for (const auto &[x, y]: coords) {
            collectibles_.emplace_back(
                factory(
                    static_cast<uint16_t>(x * TILE_SQ_SIZE),
                    static_cast<uint16_t>(y * TILE_SQ_SIZE)
                )
            );
        }
    };

    const auto healthCollectibleCoords = fetchCollectibleCoords(
        this->gameMap_->getMap(), MapDescription::TILE_ID::HEALTH_COLLECTIBLE_ID
    );
    const auto scoreCollectibleCoords = fetchCollectibleCoords(
        this->gameMap_->getMap(), MapDescription::TILE_ID::SCORE_COLLECTIBLE_ID
    );

    collectibles_.reserve(healthCollectibleCoords.size() + scoreCollectibleCoords.size());

    emplaceCollectiblesForType(
        [](const uint16_t x, const uint16_t y) { return HealthCollectible{x, y}; },
        healthCollectibleCoords
    );
    emplaceCollectiblesForType(
        [](const uint16_t x, const uint16_t y) { return ScoreCollectible{x, y}; },
        scoreCollectibleCoords
    );
}

ModuleSwitchRequest Game_ASH::runGame() {
    while (true) {
        const uint64_t frameStart = time_us_64();

        processCurrentState();
        const uint64_t frameUs = time_us_64() - frameStart;

        if (constexpr uint64_t targetUs = FPS; frameUs < targetUs) {
            sleep_us(targetUs - frameUs);
        }
    }
}

void Game_ASH::processCurrentState() {
    switch (this->currentState_) {
        case Game_ASH_State::GAMEPLAY:
            processGameplayState();
            break;
        case Game_ASH_State::PAUSED:
            processPausedState();
            break;
        case Game_ASH_State::MENU:
            processMenuState();
            break;
    }
}

void Game_ASH::processGameplayState() {
    this->display_.clear(BLACK);
    InputEngine::inputListener(*this->eventQueue_);
    CollisionScanner::scanForAllCollisions(*this->collisionEventQueue_, *this->player_, this->enemies_,
                                           this->collectibles_);
    updatePlayer();
    updateEnemies(this->player_->getPosX());
    updateCollectibles();
    drainCollisionQueue();
    removeDeadEnemies();
    updateMap();
    drawMap();
    drawPlayer();
    drawEnemies();
    drawCollectibles();
    drawHud();
    this->display_.update();

    if (this->enemies_.empty()) {
        this->nextLevel();
    }
}

void Game_ASH::processMenuState() {
    // todo
}

void Game_ASH::processPausedState() {
    // todo
}

void Game_ASH::drawMap() {
    this->gameMap_->draw(
        this->display_, this->gameMap_->getBackgroundAsset(), this->gameMap_->getTileWalkableAsset()
    );
}

void Game_ASH::drawPlayer() const {
    this->player_->draw();
}

void Game_ASH::drawEnemies() const {
    for (const auto &enemy: enemies_) {
        enemy->draw();
    }
}

void Game_ASH::drawHud() const {
    const std::string msgLvl = "LEVEL: " + std::to_string(currentLevel_);
    drawString(HUD_X, HUD_Y, msgLvl, &Font8, BLACK, WHITE);
    const std::string msgScore = "SCORE: " + std::to_string(this->player_->getScore());
    drawString(display::WIDTH - HUD_X - textWidth(msgScore, Font8), HUD_Y, msgScore, &Font8, BLACK, WHITE);
}

void Game_ASH::drawCollectibles() const {
    for (const auto &collectible: collectibles_) {
        std::visit([](const auto &c) {
            c.draw();
        }, collectible);
    }
}

void Game_ASH::updatePlayer() const {
    drainInputQueue();
    this->player_->setCameraPosX(this->gameMap_->getCameraX() * TILE_SQ_SIZE);
    this->player_->updateJump();
    this->player_->updateAttack();
}

void Game_ASH::updateCollectibles() {
    const auto cameraX = this->gameMap_->getCameraX();
    for (auto &collectible: collectibles_) {
        std::visit([cameraX](auto &c) {
            c.setCameraPosX(cameraX * TILE_SQ_SIZE);
        }, collectible);
    }
}

void Game_ASH::updateEnemies(const uint16_t playerPosX) const {
    for (const auto &enemy: enemies_) {
        enemy->setCameraPosX(
            gameMap_->getCameraX() * TILE_SQ_SIZE
        );
        enemy->followPlayer(playerPosX);
    }
}

void Game_ASH::updateMap() const {
    gameMap_->updateCamera(this->player_->getPosX() / TILE_SQ_SIZE, this->gameMap_->getMap());
}

void Game_ASH::drainCollisionQueue() {
    while (!this->collisionEventQueue_->empty()) {
        if (const auto event = this->collisionEventQueue_->front(); std::holds_alternative<
            CollisionScanner::PlayerCollisionEvent>(event)) {
            const auto &pce = std::get<CollisionScanner::PlayerCollisionEvent>(event);

            if (this->player_->canGiveDamageInFrame()) {
                pce.hitWith.takeDamage(Player::PLAYER_DAMAGE);
            }

            if (pce.hitWith.isDamagePossible() && !pce.hitWith.isGivenDamageInFrame()) {
                pce.hitWith.setGivenDamageInFrame(true);
                this->player_->takeDamage(Enemy::ENEMY_DAMAGE);
            }

            pce.hitWith.setCurrentState(EnemyState::ATTACKING);
        } else if (std::holds_alternative<CollisionScanner::EnemyCollisionEvent>(event)) {
            const auto &ece = std::get<CollisionScanner::EnemyCollisionEvent>(event);

            const uint16_t e1X = ece.e1.getPosX();

            if (const uint16_t e2X = ece.e2.getPosX(); e1X < e2X) {
                ece.e2.setPosX(e1X + Enemy::ENEMY_SEPARATION);
            } else if (e2X < e1X) {
                ece.e1.setPosX(e2X + Enemy::ENEMY_SEPARATION);
            }
        } else if (std::holds_alternative<CollisionScanner::CollectibleCollisionEvent>(event)) {
            const auto &cce = std::get<CollisionScanner::CollectibleCollisionEvent>(event);

            const auto it = std::find_if(
                collectibles_.begin(),
                collectibles_.end(),
                [&cce](auto &item) {
                    return std::visit(
                        [&cce](auto &collectible) {
                            return static_cast<BaseCollectible *>(&collectible)
                                   == &cce.collectible;
                        },
                        item
                    );
                }
            );

            if (it != collectibles_.end()) {
                std::visit(
                    [&cce]([[maybe_unused]] auto &collectible) {
                        using T = std::decay_t<decltype(collectible)>;

                        if constexpr (std::is_same_v<T, HealthCollectible>) {
                            cce.target.heal(HealthCollectible::HEALTH_VALUE);
                        } else if constexpr (std::is_same_v<T, ScoreCollectible>) {
                            cce.target.updateScore(300);
                        }
                    },
                    *it
                );
                collectibles_.erase(it);
            }
        }

        this->collisionEventQueue_->pop();
    }
}

void Game_ASH::drainInputQueue() const {
    while (!this->eventQueue_->empty()) {
        if (const auto [state, button] = eventQueue_->front();
            state == InputEngine::ButtonState::PRESSED
        ) {
            switch (button) {
                case InputEngine::BUTTONS.at(ASH_GAMEPLAY_BUTTONS::BUTTON_LEFT):
                    this->player_->moveHorizontally(true, BaseMap::getMapWidth());
                    break;
                case InputEngine::BUTTONS.at(ASH_GAMEPLAY_BUTTONS::BUTTON_RIGHT):
                    this->player_->moveHorizontally(false, BaseMap::getMapWidth());
                    break;
                case InputEngine::BUTTONS.at(ASH_GAMEPLAY_BUTTONS::BUTTON_JUMP):
                    this->player_->startJump();
                    break;
                case InputEngine::BUTTONS.at(ASH_GAMEPLAY_BUTTONS::BUTTON_ATTACK):
                    this->player_->attack();
                    break;
                default:
                    break;
            }
        }
        eventQueue_->pop();
    }
}

void Game_ASH::nextLevel() {
    if (this->currentLevel_++ == 1) {
        this->gameMap_ = std::make_unique<MapLVL2>();
    } else {
        return;
    }

    this->eventQueue_ = std::make_unique<std::queue<InputEngine::ButtonEvent> >();
    this->collisionEventQueue_ = std::make_unique<std::queue<CollisionScanner::CollisionEvent> >();

    this->enemies_.clear();
    this->collectibles_.clear();

    this->player_->setPosX(INITIAL_PLAYER_TILE_X * TILE_SQ_SIZE);
    this->player_->setPosY(INITIAL_PLAYER_TILE_Y * TILE_SQ_SIZE);
    this->player_->setMap(this->gameMap_.get());

    spawnEnemies();
    spawnCollectibles();
}
