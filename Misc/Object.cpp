//
// Created by kgbcomrade on 4/29/20.
//

#include "Object.h"
#include <cstdlib>

int Object::GetPropertyInt(const std::string& pName) {
    return (int) strtol(properties[pName].c_str(), nullptr, 10);
}

float Object::GetPropertyFloat(const std::string& pName) {
    return (float) strtod(properties[pName].c_str(), nullptr);
}

std::string Object::GetPropertyString(const std::string& pName) {
    return properties[pName];
}
