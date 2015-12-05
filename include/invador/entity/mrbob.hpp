#ifndef MRBOB_HPP_
#define MRBOB_HPP_

#include <invador/entity/entity.hpp>

enum class BobState {
	Idle = 0,
	Shooting
};

class MrBob : public Entity {
public:
	MrBob(Game * game, vec2 pos);
	virtual ~MrBob();

	void update(Game * game);
	bool isHit(vec2 pos);
private:
	BobState state;
	double stateIdx;
};

#endif