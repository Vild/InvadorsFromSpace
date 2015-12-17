#include <invador/entity/missalice.hpp>
#include <invador/game.hpp>
#include <invador/entity/projectile.hpp>

#include <iostream>
#include <cmath>
#include <cstdlib>

MissAlice::MissAlice(Game * game, vec2 pos) : TexturedEntity(pos, game->getResources().getTexture(Textures::MissAlice), 4), state(AliceState::Idle), stateIdx(0) {
	stateIdx = (rand() % 20);
}

MissAlice::~MissAlice() {
}

void MissAlice::update(Game * game) {
	//const double speed = 600;
	double d = game->getDelta();
	stateIdx += d * 8;

	//getOffset().x = sin(game->getTime()*2)*4*getScale();
	getOffset().y = abs(sin(game->getTime()*4)*2*getScale());

	if (stateIdx > 16 && state != AliceState::Shooting) {
		state = AliceState::Shooting;
		stateIdx = 0;

		vec2 spawnPos = getPos() + getOffset();
		spawnPos.y += getTexture()->getSize().y * getScale() / 8;
		spawnPos.y += 4 * getScale();
		game->addEntity(new Projectile(game, spawnPos, vec2(0, 400), 0));
	}

	if (state == AliceState::Shooting && stateIdx >= 4) {
		state = AliceState::Idle;
		stateIdx = 0;
	}

	if (state == AliceState::Idle) {
		setFrame((int)stateIdx % 4);
	} else if (state == AliceState::Shooting) {
		setFrame((int)stateIdx % 4 + 4);
	}
}

vector<Hitbox> MissAlice::getHitboxes() const {
	return vector<Hitbox>({Hitbox(vec2(1*getScale(), 0*getScale()), vec2(14*getScale(), 14*getScale()))});
}

std::string MissAlice::toString() const {
	return "MissAlice";
}
