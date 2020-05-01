//
// Created by kgbcomrade on 5/1/20.
//

#include "Layer.h"

Layer::~Layer() {
    for(auto &i : tiles)
        delete i;
}

