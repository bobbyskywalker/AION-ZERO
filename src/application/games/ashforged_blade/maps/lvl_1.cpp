#include "lvl_1.hpp"

#include <cstdint>

void MapLVL1::draw(display::LcdDisplay &display) {
    drawBg(display);

    for (uint8_t y = 0; y < MAP_HEIGHT; ++y) {
        for (uint8_t x = 0; x < CAMERA_SIZE; ++x) {
            if (const uint8_t tile = camera_[y][x]; tile == MapDescription::TILE_WALKABLE_ID) {
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
    for (uint8_t y = 0; y < display::HEIGHT; y++) {
        for (uint8_t x = 0; x < display::WIDTH; x++) {
            const uint8_t srcX = (x + this->scrollX_) % display::WIDTH;
            const uint16_t index = (y * display::WIDTH + srcX) * 2;
            const uint16_t color = BACKGROUND[index] | BACKGROUND[index + 1] << 8;
            drawPixel(x, y, color);
        }
    }
}

void MapLVL1::updateCamera(const uint16_t playerPosX) {
    if (const uint16_t screenTileX = static_cast<int16_t>(playerPosX) - static_cast<int16_t>(cameraX_);
            screenTileX >= CAMERA_SIZE)
    {
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

bool MapLVL1::isWalkableTileOnPos(const uint16_t posX,const uint16_t posY) const {
    // todo: throw 2 to const if this offset persists
    for (uint8_t y = 0; y <= 2; ++y) {
        if (posY < y) {
            continue;
        }
        if (MAP_LVL1[posY - y][posX] == MapDescription::TILE_WALKABLE_ID) {
            return true;
        }
    }

    return false;
}

bool MapLVL1::isGroundOnPos(const uint16_t posY) const {
    return posY == INITIAL_PLAYER_TILE_Y;
}

std::vector<std::pair<uint8_t, uint8_t>> MapLVL1::provideEnemyCoordinates() {
    std::vector<std::pair<uint8_t, uint8_t>> coordinates;

    for (uint8_t y = 0; y < MAP_HEIGHT; ++y) {
        for (uint8_t x = 0; x < MAP_WIDTH; ++x) {
            if (MAP_LVL1[y][x] == MapDescription::ENEMY_POS_ID) {
                coordinates.emplace_back(x, y);
            }
        }
    }

    return coordinates;
}
