#ifndef PROJECTILE_HPP_
#define PROJECTILE_HPP_

#include <invador/entity/entity.hpp>

class Projectile : public Entity {
public:
	Projectile(Game * game, vec2 pos, vec2 velocity);
	virtual ~Projectile();

	void update(Game * game);
	bool isHit(vec2 pos);
private:
	vec2 velocity;
};

#endif
