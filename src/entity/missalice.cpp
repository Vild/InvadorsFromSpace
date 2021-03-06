#include <invador/entity/missalice.hpp>
#include <invador/game.hpp>
#include <invador/entity/projectile.hpp>

#include <iostream>
#include <cmath>
#include <cstdlib>

MissAlice::MissAlice(Game *game, vec2 pos, vec2 grid)
    : TexturedEntity(pos, game->getResources().getTexture(Textures::MissAlice), 4),
      state(AliceState::Idle), stateIdx(0), grid(grid), time(0) {
	stateIdx = (rand() % 20);
}

MissAlice::~MissAlice() {}

void MissAlice::update(Game *game) {
	if (game->getActive()) {
		time += game->getDelta();
		// const double speed = 600;
		double d = game->getDelta();
		stateIdx += d * 8;

		getOffsetRef().x = sin(time * 2) * 4 * getScale();
		getOffsetRef().y = abs(sin(time * 4) * 2 * getScale());
		getPosRef().y += d * 5;

		if (getPosRef().y + getOffsetRef().y >= 1000 - (80 * getScale()))
			game->setState(GameState::Lost);

		if (stateIdx > 24 && state != AliceState::Shooting &&
		    !game->getMissAlices(vec2(grid.x, grid.y + 1))) {
			state = AliceState::Shooting;
			stateIdx = 0;

			vec2 spawnPos = getPosRef() + getOffsetRef();
			spawnPos.y += getTexture()->getSize().y * getScale() / 8;
			spawnPos.y += 9 * getScale();
			spawnPos.x += 10;
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
}

vector<Hitbox> MissAlice::getHitboxes() const {
	return vector<Hitbox>({Hitbox(vec2(1 * getScale(), 0 * getScale()),
	                              vec2(14 * getScale(), 14 * getScale()))});
}

std::string MissAlice::toString() const {
	return "MissAlice";
}
