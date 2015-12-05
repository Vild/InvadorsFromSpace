#include <invador/entity/projectile.hpp>
#include <invador/game.hpp>

#include <iostream>

Projectile::Projectile(Game * game, vec2 pos, vec2 velocity, double rotate) : Entity(game->getResources().getTexture(Textures::Projectile), pos, 4), velocity(velocity), rotate(rotate) {
}

Projectile::~Projectile() {
}

void Projectile::update(Game * game) {
	setFrame((int)(game->getTime()*20) % 4 +((int)rotate / 90)*4);
	getPos() += velocity * game->getDelta();
	if (getPos().y < (int)(getTexture().getSize().y*getScale()) / -2 ||
			getPos().y > game->getWindow().getSize().y)
		getDead() = true;
}

bool Projectile::isHit(vec2 pos) {
	return false;
}
