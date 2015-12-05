#ifndef TESTGUY_HPP_
#define TESTGUY_HPP_

#include <invador/entity/entity.hpp>

class TestGuy : public Entity {
public:
	TestGuy(Game * game, vec2 pos);
	virtual ~TestGuy();

	void update(Game * game);
	bool isHit(vec2 pos);
};

#endif
