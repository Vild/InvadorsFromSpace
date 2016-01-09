#include <invador/hitbox.hpp>

Hitbox::Hitbox(vec2 offset, vec2 size)
    : offset(offset), size(size) {}

bool Hitbox::isHit(vec2 pos) {
	pos -= offset;

	return pos.x > 0 && pos.x <= size.x && pos.y > 0 && pos.y <= size.y;
}

vec2 Hitbox::getOffset() const {
	return offset;
}

vec2 Hitbox::getSize() const {
	return size;
}
