#include "lvl_1.hpp"

#include <cstdint>

void MapLVL1::draw(display::LcdDisplay &display) {
    drawBg(display);

    for (uint8_t y = 0; y < 16; ++y) {
        for (uint8_t x = 0; x < 16; ++x) {
            if (const uint8_t tile = camera_[y][x]; tile == 1) {
                drawTile(
                    display,
                    TILE_WALKABLE,
                    x * TILE_SQ_SIZE,
                    y * TILE_SQ_SIZE,
                    TILE_SQ_SIZE,
                    TILE_SQ_SIZE
                );
            }
        }
    }
}

void MapLVL1::drawBg(display::LcdDisplay &display) {
    for (uint8_t y = 0; y < 128; y++) {
        for (uint8_t x = 0; x < 128; x++) {

            const uint8_t srcX = (x + this->scrollX_) % 128;

            const uint16_t index = (y * 128 + srcX) * 2;

            const uint16_t color = BACKGROUND[index] | BACKGROUND[index + 1] << 8;

            drawPixel(x, y, color);
        }
    }
}

void MapLVL1::updateCamera(const uint16_t playerPosX) {
    const int16_t screenTileX =
        static_cast<int16_t>(playerPosX) -
        static_cast<int16_t>(cameraX_);

    if (screenTileX >= CAMERA_SIZE) {
        cameraX_ = playerPosX - CAMERA_SIZE + 1;
    }

    else if (screenTileX < 0) {
        cameraX_ = playerPosX;
    }

    if (cameraX_ > MAP_WIDTH - CAMERA_SIZE) {
        cameraX_ = MAP_WIDTH - CAMERA_SIZE;
    }

    for (size_t y = 0; y < CAMERA_SIZE; ++y) {
        for (size_t x = 0; x < CAMERA_SIZE; ++x) {
            camera_[y][x] = MAP_LVL1[y][cameraX_ + x];
        }
    }
}
