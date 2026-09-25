#ifndef AION_ZERO_FMW_ENEMY_HPP
#define AION_ZERO_FMW_ENEMY_HPP

#include <cstdint>

#include "../base_entity.hpp"

class Enemy : public BaseEntity {
private:

public:
    void draw() override;
    void update();
};


#endif //AION_ZERO_FMW_ENEMY_HPP