#ifndef HITBOX_HPP_
#define HITBOX_HPP_

#include <invador/data.hpp>

class Hitbox {
public:
	Hitbox(vec2 offset, vec2 size);

	bool isHit(vec2 pos);

	vec2 getOffset() const;
	vec2 getSize() const;

private:
	vec2 offset;
	vec2 size;
};

#endif
