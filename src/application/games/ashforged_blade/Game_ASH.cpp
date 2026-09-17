#include "Game_ASH.hpp"

#include "Module_ASH.hpp"
#include "../../../engine/input.hpp"

Game_ASH::Game_ASH(display::LcdDisplay& display) : currentState_(Game_ASH_State::GAMEPLAY), display_(display) {
    this->eventQueue_ = std::make_unique<std::queue<InputEngine::ButtonEvent>>();
    this->gameMap_ = std::make_unique<MapLVL1>();
    this->player_ = std::make_unique<Player>(INITIAL_PLAYER_TILE_X * TILE_SQ_SIZE, INITIAL_PLAYER_TILE_Y * TILE_SQ_SIZE);
}

ModuleSwitchRequest Game_ASH::runGame() {
    while (true) {
        const uint64_t frameStart = time_us_64();

        processCurrentState();
        const uint64_t frameUs = time_us_64() - frameStart;

        if (constexpr uint64_t targetUs = 33'000; frameUs < targetUs) {
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
    drawMap();
    drawPlayer();
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
    drawSprite(
        IDLE,
        player_->getPosX(),
        player_->getPosY(),
        PLAYER_SQ_SIZE,
        PLAYER_SQ_SIZE
    );
}

void Game_ASH::updatePlayer() const {
    while (!this->eventQueue_->empty()) {
        if (const auto [state, button] = eventQueue_->front();
            state == InputEngine::ButtonState::PRESSED
        ) {
            switch (button) {
                case InputEngine::BUTTONS.at( ASH_GAMEPLAY_BUTTONS::BUTTON_LEFT):
                    this->player_->setPosX(this->player_->getPosX() - STEP_SIZE);
                    break;
                case InputEngine::BUTTONS.at( ASH_GAMEPLAY_BUTTONS::BUTTON_RIGHT):
                    this->player_->setPosX(this->player_->getPosX() + STEP_SIZE);
                    break;
                default:
                    break;
            }
            eventQueue_->pop();
        }
    }
}
