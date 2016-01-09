#ifndef MRBOB_HPP_
#define MRBOB_HPP_

#include <invador/entity/texturedentity.hpp>

enum class BobState { Idle = 0, Shooting };

class MrBob : public TexturedEntity {
      public:
	MrBob(Game *game, vec2 pos);
	virtual ~MrBob();

	void update(Game *game);
	vector<Hitbox> getHitboxes() const;

	virtual std::string toString() const;

      private:
	BobState state;
	double stateIdx;
};

#endif
