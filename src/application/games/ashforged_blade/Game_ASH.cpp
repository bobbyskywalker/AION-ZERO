#include "Game_ASH.hpp"

#include "Module_ASH.hpp"

Game_ASH::Game_ASH(display::LcdDisplay& display) : display_(display) {
    this->gameMap_ = std::make_unique<MapLVL1>();
    this->player_ = std::make_unique<Player>(INITIAL_PLAYER_TILE_X * TILE_SQ_SIZE, INITIAL_PLAYER_TILE_Y * TILE_SQ_SIZE);
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
        IDLE,//tmp
        player_->getPosX(),
        player_->getPosY(),
        PLAYER_SQ_SIZE,
        PLAYER_SQ_SIZE
    );
}
