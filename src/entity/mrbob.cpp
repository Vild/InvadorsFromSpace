#include <invador/entity/mrbob.hpp>
#include <invador/game.hpp>
#include <invador/entity/projectile.hpp>

#include <iostream>
#include <cmath>

MrBob::MrBob(Game * game, vec2 pos) : Entity(game->getResources().getTexture(Textures::MrBob), pos, 4), state(BobState::Idle), stateIdx(0) {
}

MrBob::~MrBob() {
}

void MrBob::update(Game * game) {
	const double speed = 600;
	double d = game->getDelta();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		getPos().y -= d * speed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		getPos().y += d * speed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		getPos().x -= d * speed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		getPos().x += d * speed;

	stateIdx += d * 8;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && state != BobState::Shooting) {
		state = BobState::Shooting;
		stateIdx = 0;

		vec2 spawnPos = getPos() + getOffset();
		spawnPos.y -= getTexture().getSize().y * getScale()/8;
		spawnPos.x = (int)spawnPos.x;
		spawnPos.y = (int)spawnPos.y;
		game->addEntity(new Projectile(game, spawnPos, vec2(0, -400), 180));
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

bool MrBob::isHit(vec2 pos) {
	return false;
}
