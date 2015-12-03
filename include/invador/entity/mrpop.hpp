#ifndef MRPOP_HPP_
#define MRPOP_HPP_

#include <invador/entity/entity.hpp>

class MrPop : public Entity {
public:
	MrPop(Game * game, vec2 pos);
	virtual ~MrPop();

	void update(Game * game);
	bool isHit(vec2 pos);
private:
	vec2 velocity;
};

#endif
