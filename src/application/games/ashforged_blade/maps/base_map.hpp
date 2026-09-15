#ifndef AION_ZERO_FMW_BASE_MAP_HPP
#define AION_ZERO_FMW_BASE_MAP_HPP

class BaseMap {
public:
    virtual ~BaseMap() = default;
    virtual void draw(display::LcdDisplay& display) = 0;
};

#endif //AION_ZERO_FMW_BASE_MAP_HPP