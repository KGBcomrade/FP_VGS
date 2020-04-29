//
// Created by kgbcomrade on 4/29/20.
//

#include "Object.h"
#include <cstdlib>

int Object::GetPropertyInt(const std::string& pName) {
    return (int) strtod(properties[pName].c_str(), nullptr);
}

float Object::GetPropertyFloat(const std::string& pName) {
    return (float) strtod(properties[pName].c_str(), nullptr);
}

std::string Object::GetPropertyString(const std::string& pName) {
    return properties[pName];
}
