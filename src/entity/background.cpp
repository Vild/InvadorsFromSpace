#include <invador/entity/background.hpp>
#include <invador/game.hpp>
#include <invador/entity/projectile.hpp>

#include <SFML/Graphics.hpp>

#include <iostream>
#include <cmath>

#include <sys/stat.h>

Background::Background(Game * game) : Entity(game->getResources().getTexture(Textures::Background), vec2(0, 0), 1), block(sf::Vector2f(10, 10)), offset(0, 0) {
	getTexture().setRepeated(true);
	getSprite().setScale(sf::Vector2f(getScale(), getScale()));

	shader = new sf::Shader();
	shader->loadFromFile("res/shader/background.vert", "res/shader/background.frag");
}

Background::~Background() {
	delete shader;
}

struct stat oldStat;
void Background::render(Game * game) {
	struct stat newStat;

	stat("res/shader/background.frag", &newStat);

	if (newStat.st_mtime != oldStat.st_mtime) {
		std::cout << "Reloading shaders!" << std::endl;
		delete shader;
		shader = new sf::Shader();
		shader->loadFromFile("res/shader/background.vert", "res/shader/background.frag");
	}

	oldStat = newStat;

	game->getWindow().setView(sf::View(sf::FloatRect(0, 0, game->getWindow().getSize().x, game->getWindow().getSize().y)));
	block.setSize(sf::Vector2f(game->getWindow().getSize().x, game->getWindow().getSize().y));

	shader->setParameter("offset", offset.x, offset.y);
	game->getWindow().draw(block, shader);
	//Entity::render(game);
}

void Background::update(Game * game) {
	//auto s = game->getWindow().getSize();
	//auto d = game->getDelta()*100;
	auto t = game->getTime() * 100 / 8.0;
	offset.x = t;
	offset.y = t;

	if (game->getActive() && sf::Keyboard::isKeyPressed(sf::Keyboard::F5)) {
		std::cout << "Reloading shaders!" << std::endl;
		delete shader;
		shader = new sf::Shader();
		shader->loadFromFile("res/shader/background.vert", "res/shader/background.frag");
	}
}

bool Background::isHit(vec2 pos) {
	return false;
}


double Background::getScale() const {
	return 1.0;
}