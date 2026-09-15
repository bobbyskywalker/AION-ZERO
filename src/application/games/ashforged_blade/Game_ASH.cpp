#include "Game_ASH.hpp"

#include "Module_ASH.hpp"

Game_ASH::Game_ASH(display::LcdDisplay& display) : display_(display) {
    this->gameMap_ = std::make_unique<MapLVL1>();
}

ModuleSwitchRequest Game_ASH::runGame() {
    while (true) {
        this->display_.clear(BLACK);
        drawMap();
        drawPlayer();
        this->display_.update();
        sleep_ms(16);
    }
}

void Game_ASH::drawMap() {
    this->gameMap_->draw(this->display_);
}

void Game_ASH::drawPlayer() const {
    drawSprite(
        player,
        (display::WIDTH - PLAYER_SQ_SIZE) / 2,
        (display::HEIGHT - PLAYER_SQ_SIZE) / 2,
        PLAYER_SQ_SIZE,
        PLAYER_SQ_SIZE
    );
}
