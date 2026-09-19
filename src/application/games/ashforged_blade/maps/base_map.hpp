#ifndef AION_ZERO_FMW_BASE_MAP_HPP
#define AION_ZERO_FMW_BASE_MAP_HPP

constexpr uint8_t TILE_SQ_SIZE = 8;
constexpr uint8_t PLAYER_SQ_SIZE = 16;
constexpr uint8_t INITIAL_PLAYER_TILE_X = 7;
constexpr uint8_t INITIAL_PLAYER_TILE_Y = 9;

class BaseMap {
public:
    virtual ~BaseMap() = default;
    virtual void draw(display::LcdDisplay& display) = 0;
};

#endif //AION_ZERO_FMW_BASE_MAP_HPP