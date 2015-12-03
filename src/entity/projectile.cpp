#include <invador/entity/projectile.hpp>
#include <invador/game.hpp>

#include <iostream>

#define SCALE 5

Projectile::Projectile(Game * game, vec2 pos, vec2 velocity) : Entity(game->getResources().getTexture(Textures::PROJECTILE), pos, 2), velocity(velocity) {
	getTexture().setSmooth(false);
	getSprite().setScale(sf::Vector2f(SCALE, SCALE));
}

Projectile::~Projectile() {
}

void Projectile::update(Game * game) {
	setFrame((int)(game->getTime()*20) % 4);
	getPos() += velocity * game->getDelta();
	if (getPos().y < (int)(getTexture().getSize().y*SCALE) / -2 ||
			getPos().y > game->getWindow().getSize().y)
		getDead() = true;
}

bool Projectile::isHit(vec2 pos) {
	return false;
}
