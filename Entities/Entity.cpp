//
// Created by kgbcomrade on 4/29/20.
//

#include "Entity.h"

Entity::Entity(sf::Texture * texture, const sf::String &name, sf::Vector2f position, sf::Vector2f size, Level & level)  {
    this->name = name;
    this->position = position;
    this->size = size;
    sprite = new sf::Sprite(*texture);
    obj = level.getAllObjects();
    life = true;
    health = 1;
    speed = .2;
}

sf::FloatRect Entity::getRect() {
    return sf::FloatRect(position, size);
}

void Entity::update(float dt) {
    position += velocity * dt;
    sprite->setPosition(position);
    checkCollisionWithMap(velocity);
    if(health <=0 )
        life = false;
}

void Entity::checkCollisionWithMap(sf::Vector2f dvec) {
    for (auto & i : obj) {
        if (getRect().intersects(i->rect)) {
            if (i->name == "solid") {
                if(dvec.x > 0) {
                    position.x = i->rect.left - size.x;
                }
                if(dvec.x < 0) {
                    position.x = i->rect.left + i->rect.width;
                }
                if(dvec.y > 0) {
                    position.y = i->rect.top - size.y;
                    velocity.y = 0;
                }
                if(dvec.y < 0) {
                    position.y = i->rect.top + i->rect.height;
                    velocity.y = 0;
                }
			}
//					if (Dy > 0) { y = obj[i].rect.top - h; dy = 0; }
//					if (Dy < 0) { y = obj[i].rect.top + obj[i].rect.height; dy = 0; }
//					if (Dx > 0) { x = obj[i].rect.left - w; }
//					if (Dx < 0) { x = obj[i].rect.left + obj[i].rect.width; }
		}
    }

}

sf::Sprite *Entity::getSprite() {
    return sprite;
}

Entity::~Entity() {
//    delete sprite->getTexture();
    delete sprite;
}





