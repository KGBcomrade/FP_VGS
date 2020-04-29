//
// Created by kgbcomrade on 4/29/20.
//

#ifndef FP2_OBJECT_H
#define FP2_OBJECT_H


#include <string>
#include <SFML/Graphics/Rect.hpp>
#include <map>
#include <SFML/Graphics/Sprite.hpp>

class Object {
public:

    std::map<std::string, std::string> properties;


    std::string name, type;

    sf::Rect<float> rect;
    sf::Sprite sprite;
    int GetPropertyInt(const std::string& pName);
    float GetPropertyFloat(const std::string& pName);
    std::string GetPropertyString(const std::string& pName);
};


#endif //FP2_OBJECT_H
