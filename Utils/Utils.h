//
// Created by kgbcomrade on 5/1/20.
//

#include <SFML/System/Vector2.hpp>
#include <cmath>

#ifndef FP2_UTILS_H
#define FP2_UTILS_H

#endif //FP2_UTILS_H

float vectorLen(sf::Vector2f vector) {
    return std::sqrt(vector.x * vector.x + vector.y * vector.y);
}