#ifndef MISSALICE_HPP_
#define MISSALICE_HPP_

#include <invador/entity/texturedentity.hpp>

enum class AliceState {
	Idle = 0,
	Shooting
};

class MissAlice : public TexturedEntity {
public:
	MissAlice(Game * game, vec2 pos);
	virtual ~MissAlice();

	void update(Game * game);
	vector<Hitbox> getHitboxes() const;

	virtual std::string toString() const;
private:
	AliceState state;
	double stateIdx;
};

#endif
