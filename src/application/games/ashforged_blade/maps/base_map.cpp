#include "base_map.hpp"

#include <algorithm>

void BaseMap::drawBg([[maybe_unused]] display::LcdDisplay &display, const unsigned char* bg) const {
    for (uint8_t y = 0; y < display::HEIGHT; y++) {
        for (uint8_t x = 0; x < display::WIDTH; x++) {
            const uint8_t srcX = (x + this->scrollX_) % display::WIDTH;
            const uint16_t index = (y * display::WIDTH + srcX) * 2;
            const uint16_t color = bg[index] | bg[index + 1] << 8;
            drawPixel(x, y, color);
        }
    }
}

void BaseMap::draw(
    display::LcdDisplay &display,
    const unsigned char* backgroundAsset,
    const unsigned char* tileWalkableAsset
) const {
    drawBg(display, backgroundAsset);

    for (uint8_t y = 0; y < MAP_HEIGHT; ++y) {
        for (uint8_t x = 0; x < CAMERA_SIZE; ++x) {
            if (const uint8_t tile = camera_[y][x];
                    tile == static_cast<uint8_t>(MapDescription::TILE_ID::TILE_WALKABLE_ID)) {
                drawTile(
                    display,
                    tileWalkableAsset,
                    x * TILE_SQ_SIZE,
                    y * TILE_SQ_SIZE,
                    TILE_SQ_SIZE,
                    TILE_SQ_SIZE
                );
                    }
        }
    }
}

std::vector<std::pair<uint8_t, uint8_t> > BaseMap::provideTypeCoordinates(
    const std::array<std::array<uint8_t, MAP_WIDTH>, MAP_HEIGHT> &map, MapDescription::TILE_ID type) {
    std::vector<std::pair<uint8_t, uint8_t> > coordinates;

    for (uint8_t y = 0; y < MAP_HEIGHT; ++y) {
        for (uint8_t x = 0; x < MAP_WIDTH; ++x) {
            if (map[y][x] == static_cast<uint8_t>(type)) {
                coordinates.emplace_back(x, y);
            }
        }
    }
    return coordinates;
}

void BaseMap::updateCamera(
    const uint16_t playerPosX,
    const std::array<std::array<uint8_t, MAP_WIDTH>, MAP_HEIGHT>& map)
{
    constexpr int LEVEL_WIDTH = 16;

    const int levelStart =
        (playerPosX / LEVEL_WIDTH) * LEVEL_WIDTH;
    const int levelEnd = levelStart + LEVEL_WIDTH;

    if (const int screenTileX =static_cast<int>(playerPosX) - static_cast<int>(cameraX_); screenTileX >= CAMERA_SIZE) {
        cameraX_ = playerPosX - CAMERA_SIZE + 1;
    } else if (screenTileX < 0) {
        cameraX_ = playerPosX;
    }

    const int minCameraX = levelStart;
    const int maxCameraX = levelEnd - CAMERA_SIZE;

    cameraX_ = static_cast<uint16_t>(
        std::clamp(static_cast<int>(cameraX_), minCameraX, maxCameraX)
    );

    for (size_t y = 0; y < CAMERA_SIZE; ++y) {
        for (size_t x = 0; x < CAMERA_SIZE; ++x) {
            camera_[y][x] = map[y][cameraX_ + x];
        }
    }
}

bool BaseMap::isWalkableTileOnPos(
    const uint16_t posX,
    const uint16_t posY,
    const std::array<std::array<uint8_t, MAP_WIDTH>, MAP_HEIGHT> & map
) const
{
    // todo: throw 2 to const if this offset persists
    for (uint8_t y = 0; y <= 2; ++y) {
        if (posY < y) {
            continue;
        }
        if (map[posY - y][posX] == static_cast<uint8_t>(MapDescription::TILE_ID::TILE_WALKABLE_ID)) {
            return true;
        }
    }

    return false;
}

bool BaseMap::isGroundOnPos(const uint16_t posY) const {
    return posY == INITIAL_PLAYER_TILE_Y;
}