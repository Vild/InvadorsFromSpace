#include <invador/entity/mrbob.hpp>
#include <invador/game.hpp>
#include <invador/entity/projectile.hpp>

#include <iostream>
#include <cmath>

MrBob::MrBob(Game *game, vec2 pos)
    : TexturedEntity(pos, game->getResources().getTexture(Textures::MrBob), 4),
      state(BobState::Idle), stateIdx(0) {
}

MrBob::~MrBob() {}

void MrBob::update(Game *game) {
	if (game->getActive()) {
		const double speed = 600;
		double d = game->getDelta();

		stateIdx += d * 8;

		auto &x = getPosRef().x;
		auto &y = getPosRef().y;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
		    sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			y -= d * speed;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ||
		    sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			y += d * speed;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
		    sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			x -= d * speed;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
		    sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			x += d * speed;

		x = fmax(0, fmin(x, 1000 - (16 * getScale())));
		y = fmax(1000 - (80 * getScale()), fmin(y, 1000 - (16 * getScale())));

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) &&
		    state != BobState::Shooting) {
			state = BobState::Shooting;
			stateIdx = 0;

			vec2 spawnPos = getPosRef() + getOffsetRef();
			spawnPos.y -= getTexture()->getSize().y * getScale() / 8;
			spawnPos.y -= 4 * getScale();
			spawnPos.x += 4 * getScale();
			game->addEntity(new Projectile(game, spawnPos, vec2(0, -600), 180));
		}

		if (state == BobState::Shooting && stateIdx >= 4) {
			state = BobState::Idle;
			stateIdx = 0;
		}

		if (state == BobState::Idle) {
			setFrame((int)stateIdx % 4);
		} else if (state == BobState::Shooting) {
			setFrame((int)stateIdx % 4 + 4);
		}
	}
}

vector<Hitbox> MrBob::getHitboxes() const {
	return vector<Hitbox>({Hitbox(vec2(1 * getScale(), 1 * getScale()),
	                              vec2(14 * getScale(), 15 * getScale()))});
}

std::string MrBob::toString() const {
	return "MrBob";
}
