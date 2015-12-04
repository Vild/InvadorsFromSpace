#include <invador/entity/testguy.hpp>
#include <invador/game.hpp>
#include <invador/entity/projectile.hpp>

#include <iostream>
#include <cmath>

#define SCALE 10

TestGuy::TestGuy(Game * game, vec2 pos) : Entity(game->getResources().getTexture(Textures::TESTGUY), pos, 2){
	getTexture().setSmooth(false);
	getSprite().setScale(sf::Vector2f(SCALE, SCALE));
}

TestGuy::~TestGuy() {
}

void TestGuy::update(Game * game) {
	setFrame((int)(game->getTime()*8) % 4);
	getPos().x = 0;
	getOffset().x = cos(game->getTime()/1.0) * 400 + 400;
	getPos().y = 10;
	getOffset().y = abs(sin(game->getTime()/1.0)*200);
	if ((int)(game->getTime()*100) % 100 == 0) {
		vec2 spawnPos = getPos() + getOffset();
		spawnPos.x += (getTexture().getSize().x * SCALE) / (2*2) -
			(game->getResources().getTexture(Textures::PROJECTILE).getSize().x * 5) / (2*2);
		spawnPos.y += getTexture().getSize().y * SCALE/2;
		spawnPos.x = (int)spawnPos.x;
		spawnPos.y = (int)spawnPos.y;
		game->addEntity(new Projectile(game, spawnPos, vec2(0, 100)));
	}
}

bool TestGuy::isHit(vec2 pos) {
	return false;
}
