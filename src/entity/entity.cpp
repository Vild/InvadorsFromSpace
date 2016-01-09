#include <invador/entity/entity.hpp>
#include <assert.h>
#include <invador/game.hpp>

#include <iostream>

Entity::Entity(vec2 pos)
    : dead(false), pos(pos), offset(0, 0) {}

Entity::~Entity() {}

bool Entity::isHit(vec2 pos) {
	vector<Hitbox> boxes = getHitboxes();
	for (unsigned int i = 0; i < boxes.size(); i++) {
		if (boxes[i].isHit(pos))
			return true;
	}
	return false;
}

bool &Entity::getDeadRef() {
	return dead;
}

vec2 &Entity::getPosRef() {
	return pos;
}

vec2 &Entity::getOffsetRef() {
	return offset;
}
