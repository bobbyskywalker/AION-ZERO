#include "lvl_1.hpp"

#include <cstdint>

void MapLVL1::draw(display::LcdDisplay& display)
{
    for (uint8_t y = 0; y < 16; ++y) {
        for (uint8_t x = 0; x < 16; ++x) {

            const uint8_t tile = MAP_LVL1[y][x];
            const uint8_t* image;

            switch (tile) {
                case 2:
                    image = TILE_BOTTOM;
                    break;

                case 1:
                    image = TILE_WALKABLE;
                    break;

                default:
                    image = TILE_BACKGROUND;
                    break;
            }

            drawTile(
                display,
                image,
                x * TILE_SQ_SIZE,
                y * TILE_SQ_SIZE,
                TILE_SQ_SIZE,
                TILE_SQ_SIZE
            );
        }
    }
}