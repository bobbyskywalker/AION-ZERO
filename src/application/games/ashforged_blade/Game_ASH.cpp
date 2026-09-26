#include "Game_ASH.hpp"

#include "Module_ASH.hpp"
#include "../../../engine/input.hpp"

Game_ASH::Game_ASH(display::LcdDisplay& display) : currentState_(Game_ASH_State::GAMEPLAY), display_(display) {
    this->eventQueue_ = std::make_unique<std::queue<InputEngine::ButtonEvent>>();
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
        enemies_.emplace_back(x * TILE_SQ_SIZE, y * TILE_SQ_SIZE, 100, *this->gameMap_);
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
    updatePlayer();
    updateEnemies(this->player_->getPosX());
    updateMap();
    drawMap();
    drawPlayer();
    drawEnemies();
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

void Game_ASH::drawEnemies() {
    for (auto & enemy : enemies_) {
        enemy.draw();
    }
}

void Game_ASH::updatePlayer() const {
    drainInputQueue();
    this->player_->setCameraPosX(this->gameMap_->getCameraX() * TILE_SQ_SIZE);
    this->player_->updateJump();
}

void Game_ASH::updateEnemies(const uint16_t playerPosX) {
    for (auto & enemy : enemies_) {
        enemy.setCameraPosX(this->gameMap_->getCameraX() * TILE_SQ_SIZE);
        enemy.followPlayer(playerPosX);
    }
}

void Game_ASH::updateMap() const {
    gameMap_->updateCamera(this->player_->getPosX() / TILE_SQ_SIZE);
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
