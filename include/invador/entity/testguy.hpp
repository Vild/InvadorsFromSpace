#ifndef TESTGUY_HPP_
#define TESTGUY_HPP_

#include <invador/entity/texturedentity.hpp>

class TestGuy : public TexturedEntity {
public:
	TestGuy(Game * game, vec2 pos);
	virtual ~TestGuy();

	void update(Game * game);
	vector<Hitbox> getHitboxes() const;

	virtual std::string toString() const;
private:
	double shootDelay;
};

#endif
