#include <invador/entity/mrpop.hpp>
#include <invador/game.hpp>
#include <invador/entity/projectile.hpp>

#include <iostream>
#include <cmath>

#define SCALE 10

MrPop::MrPop(Game * game, vec2 pos) : Entity(game->getResources().getTexture(Textures::MRPOP), pos, 2){
	getTexture().setSmooth(false);
	getSprite().setScale(sf::Vector2f(SCALE, SCALE));
}

MrPop::~MrPop() {
}

void MrPop::update(Game * game) {
	setFrame((int)(game->getTime()*8) % 4);
	getOffset().x = cos(game->getTime()*15) * 2;
	if ((int)(game->getTime()*100) % 100 == 0) {
		vec2 spawnPos = getPos();
		spawnPos.x += getTexture().getSize().x * SCALE / (2*2) -
			game->getResources().getTexture(Textures::PROJECTILE).getSize().x * 4 / 2;
		spawnPos.y += getTexture().getSize().y * SCALE/2;
		game->addEntity(new Projectile(game, spawnPos, vec2(0, 100)));
	}
}

bool MrPop::isHit(vec2 pos) {
	return false;
}
