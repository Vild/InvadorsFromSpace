#include <invador/entity/testguy.hpp>
#include <invador/game.hpp>
#include <invador/entity/projectile.hpp>

#include <iostream>
#include <cmath>

TestGuy::TestGuy(Game * game, vec2 pos) : TexturedEntity(pos, game->getResources().getTexture(Textures::TestGuy), 2), shootDelay(0){
}

TestGuy::~TestGuy() {
}

void TestGuy::update(Game * game) {
	setFrame((int)(game->getTime()*8) % 4);
	getPos().x = 0;
	getOffset().x = cos(game->getTime()/1.0) * 400 + 400;
	getPos().y = 10;
	getOffset().y = abs(sin(game->getTime()/1.0)*20);

	shootDelay += game->getDelta();

	if (shootDelay > 1) {
		vec2 spawnPos = getPos() + getOffset();
		spawnPos.y += getTexture()->getSize().y * getScale() / 2;
		spawnPos.y -= 2 * getScale();
		game->addEntity(new Projectile(game, spawnPos, vec2(0, 400), 0));
		shootDelay -= 1;
	}
}

vector<Hitbox> TestGuy::getHitboxes() const {
	return vector<Hitbox>({Hitbox(vec2(1*getScale(), 5*getScale()), vec2(14*getScale(), 11*getScale()))});
}

std::string TestGuy::toString() const {
	return "TestGuy";
}
