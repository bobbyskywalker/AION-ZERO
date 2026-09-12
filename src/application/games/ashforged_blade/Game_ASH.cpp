#include "Game_ASH.hpp"

#include "Module_ASH.hpp"

Game_ASH::Game_ASH(display::LcdDisplay& display) : display_(display) {}

ModuleSwitchRequest Game_ASH::runGame() {
    while (true) {
        this->display_.clear(BLACK);
        drawMap();
        drawPlayer();
        this->display_.update();
        sleep_ms(16);
    }
}

void Game_ASH::drawTile(
    const unsigned char* image,
    const uint16_t x,
    const uint16_t y,
    const uint16_t imageWidth,
    const uint16_t imageHeight
) {
    this->display_.drawSprite(image, x, y, imageWidth, imageHeight);
}

void Game_ASH::drawMap() {
    for (uint8_t y = 0; y < 16; y++) {
        for (uint8_t x = 0; x < 16; x++) {
            drawTile(tile1, x * TILE_SQ_SIZE, y * TILE_SQ_SIZE, TILE_SQ_SIZE, TILE_SQ_SIZE);
        }
    }
}

void Game_ASH::drawPlayer() {
    drawTile(
    player,
        (display::WIDTH - PLAYER_SQ_SIZE) / 2,
        (display::HEIGHT - PLAYER_SQ_SIZE) / 2,
        PLAYER_SQ_SIZE,
        PLAYER_SQ_SIZE
    );
}
