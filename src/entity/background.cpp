#include <invador/entity/background.hpp>
#include <invador/game.hpp>
#include <invador/entity/projectile.hpp>

#include <iostream>
#include <cmath>

Background::Background(Game * game) : Entity(game->getResources().getTexture(Textures::Background), vec2(0, 0), 1) {
	getTexture().setRepeated(true);
	getSprite().setScale(sf::Vector2f(getScale(), getScale()));
}

Background::~Background() {
}

void Background::render(Game * game) {
	game->getWindow().setView(sf::View(sf::FloatRect(0, 0, game->getWindow().getSize().x, game->getWindow().getSize().y)));
	Entity::render(game);
}

void Background::update(Game * game) {
	auto s = game->getWindow().getSize();
	auto t = game->getTime() * 100;
	sf::IntRect rect;
	rect.left = (unsigned int)fmod(t, getTexture().getSize().x);
	rect.top = (int)(8-sin(t/100.0)*8.0);
	rect.width = s.x;
	rect.height = s.y;
	getSprite().setTextureRect(rect);
}

bool Background::isHit(vec2 pos) {
	return false;
}


double Background::getScale() const {
	return 1.0;
}