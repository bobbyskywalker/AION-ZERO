#include "Game_ASH.hpp"

#include "Module_ASH.hpp"
#include "../../../engine/input.hpp"
#include <algorithm>

#include "entity/enemy/enemy_state.hpp"

Game_ASH::Game_ASH(display::LcdDisplay &display) : currentState_(Game_ASH_State::GAMEPLAY), display_(display) {
    this->eventQueue_ = std::make_unique<std::queue<InputEngine::ButtonEvent> >();
    this->collisionEventQueue_ = std::make_unique<std::queue<CollisionScanner::CollisionEvent> >();
    this->gameMap_ = std::make_unique<MapLVL1>();
    this->player_ = std::make_unique<Player>(
        INITIAL_PLAYER_TILE_X * TILE_SQ_SIZE,
        INITIAL_PLAYER_TILE_Y * TILE_SQ_SIZE, Player::START_HEALTH,
        *this->gameMap_
    );
    spawnEnemies();
}

void Game_ASH::spawnEnemies() {
    const auto enemyCoords = this->gameMap_->provideEnemyCoordinates();
    enemies_.reserve(enemyCoords.size());
    for (auto [x, y]: enemyCoords) {
        enemies_.emplace_back(
            std::make_unique<Enemy>(x * TILE_SQ_SIZE, y * TILE_SQ_SIZE, 100, *this->gameMap_)
        );
    }
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
    CollisionScanner::scanForEntityCollisions(*this->collisionEventQueue_, *this->player_, this->enemies_);
    // updateHud();
    updatePlayer();
    updateEnemies(this->player_->getPosX());
    drainCollisionQueue();
    updateMap();
    drawMap();
    drawPlayer();
    drawEnemies();
    drawHud();
    this->display_.update();
}

void Game_ASH::processMenuState() {
    // todo
}

void Game_ASH::processPausedState() {
    // todo
}

void Game_ASH::drawMap() {
    this->gameMap_->draw(this->display_);
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
    const std::string msg = "LEVEL: " + std::to_string(currentLevel_);
    drawString(HUD_X, HUD_Y, msg, &Font8, BROWN, WHITE);
}

void Game_ASH::updatePlayer() const {
    drainInputQueue();
    this->player_->setCameraPosX(this->gameMap_->getCameraX() * TILE_SQ_SIZE);
    this->player_->updateJump();
    this->player_->updateAttack();
}

void Game_ASH::updateEnemies(const uint16_t playerPosX) {
    for (auto const &enemy: enemies_) {
        enemies_.erase(
            std::remove_if(
                enemies_.begin(),
                enemies_.end(),
                [](const std::unique_ptr<Enemy> &e) {return e->getHealth() == 0;}
            ),enemies_.end()
        );
        enemy->setCameraPosX(this->gameMap_->getCameraX() * TILE_SQ_SIZE);
        enemy->followPlayer(playerPosX);
    }
}

void Game_ASH::updateMap() const {
    gameMap_->updateCamera(this->player_->getPosX() / TILE_SQ_SIZE);
}

void Game_ASH::drainCollisionQueue() const {
    while (!this->collisionEventQueue_->empty()) {
        auto event = this->collisionEventQueue_->front();
        if (this->player_->canGiveDamageInFrame()) {
            event.hitWith.takeDamage(Player::PLAYER_DAMAGE);
        }
        if (event.hitWith.isDamagePossible() && !event.hitWith.isGivenDamageInFrame()) {
            event.hitWith.setGivenDamageInFrame(true);
            this->player_->takeDamage(Enemy::ENEMY_DAMAGE);
        }
        event.hitWith.setCurrentState(EnemyState::ATTACKING);
        this->collisionEventQueue_->pop();
    }
}

void Game_ASH::drainInputQueue() const {
    while (!this->eventQueue_->empty()) {
        if (const auto [state, button] = eventQueue_->front();
            state == InputEngine::ButtonState::PRESSED
        ) {
            switch (button) {
                case InputEngine::BUTTONS.at( ASH_GAMEPLAY_BUTTONS::BUTTON_LEFT):
                    this->player_->moveHorizontally(true, this->gameMap_->getMapWidth());
                    break;
                case InputEngine::BUTTONS.at( ASH_GAMEPLAY_BUTTONS::BUTTON_RIGHT):
                    this->player_->moveHorizontally(false, this->gameMap_->getMapWidth());
                    break;
                case InputEngine::BUTTONS.at( ASH_GAMEPLAY_BUTTONS::BUTTON_JUMP):
                    this->player_->startJump();
                    break;
                case InputEngine::BUTTONS.at( ASH_GAMEPLAY_BUTTONS::BUTTON_ATTACK):
                    this->player_->attack();
                    break;
                default:
                    break;
            }
            eventQueue_->pop();
        }
    }
}
