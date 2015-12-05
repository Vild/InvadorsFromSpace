#include <invador/entity/testguy.hpp>
#include <invador/game.hpp>
#include <invador/entity/projectile.hpp>

#include <iostream>
#include <cmath>

TestGuy::TestGuy(Game * game, vec2 pos) : Entity(game->getResources().getTexture(Textures::TestGuy), pos, 2){
}

TestGuy::~TestGuy() {
}

void TestGuy::update(Game * game) {
	setFrame((int)(game->getTime()*8) % 4);
	getPos().x = 0;
	getOffset().x = cos(game->getTime()/1.0) * 400 + 400;
	getPos().y = 10;
	getOffset().y = abs(sin(game->getTime()/1.0)*20);
	if ((int)(game->getTime()*100) % 100 == 0) {
		vec2 spawnPos = getPos() + getOffset();
		spawnPos.x += (getTexture().getSize().x * getScale()) / (2*2) -
			(game->getResources().getTexture(Textures::Projectile).getSize().x * getScale()) / (2*2);
		spawnPos.y += getTexture().getSize().y * getScale()/2;
		spawnPos.x = (int)spawnPos.x;
		spawnPos.y = (int)spawnPos.y;
		game->addEntity(new Projectile(game, spawnPos, vec2(0, 400), 0));
	}
}

bool TestGuy::isHit(vec2 pos) {
	return false;
}
