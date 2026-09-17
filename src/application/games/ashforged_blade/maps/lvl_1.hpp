#ifndef AION_ZERO_FMW_TEMPMAP_HPP
#define AION_ZERO_FMW_TEMPMAP_HPP

#include <array>
#include <cstdint>

#include "lvl1_assets.hpp"
#include "../../../../display/display.hpp"
#include "../util/draw.hpp"
#include "base_map.hpp"

constexpr uint8_t TILE_SQ_SIZE = 8;
constexpr uint8_t STEP_SIZE = 4;
constexpr uint8_t INITIAL_PLAYER_TILE_X = 7;
constexpr uint8_t INITIAL_PLAYER_TILE_Y = 9;

class MapLVL1 : public BaseMap {
public:
    MapLVL1() = default;
	void draw(display::LcdDisplay& display) override;

private:

    static constexpr std::array<std::array<uint8_t, 16>, 16> MAP_LVL1 = {{
        {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}}, // y = 0 bg
        {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
        {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
        {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
        {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
        {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
        {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
        {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
        {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
        {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
        {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
        {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}}, // y = 11 standing surface
        {{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2}},
        {{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2}},
        {{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2}},
        {{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2}} // y = 15
    }};
};

#endif //AION_ZERO_FMW_TEMPMAP_HPP