#include "Game_ASH.hpp"

#include "Module_ASH.hpp"

ModuleSwitchRequest Game_ASH::runGame() {
    while (true) {
        drawMap();
        printf("siema jestem w grze");
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
    Paint_DrawImage(image, x, y, imageWidth, imageHeight);
}

void Game_ASH::drawMap() {
    for (uint8_t y = 0; y < 16; y++) {
        for (uint8_t x = 0; x < 16; x++) {
            drawTile(nullptr, x * TILE_SQ_SIZE, y * TILE_SQ_SIZE, TILE_SQ_SIZE, TILE_SQ_SIZE);
        }
    }
}
