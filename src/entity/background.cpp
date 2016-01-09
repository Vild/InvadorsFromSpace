#include <invador/entity/background.hpp>
#include <invador/game.hpp>
#include <invador/entity/projectile.hpp>

#include <SFML/Graphics.hpp>

#include <iostream>
#include <cmath>

#include <sys/stat.h>

Background::Background(Game *game) : Entity(vec2(0, 0)), offset(0, 0) {
	shader = new sf::Shader();
	shader->loadFromFile("res/shader/background.vert",
	                     "res/shader/background.frag");
}

Background::~Background() {
	delete shader;
}

struct stat oldStat;
void Background::render(Game *game) {
	struct stat newStat;

	stat("res/shader/background.frag", &newStat);

	if (newStat.st_mtime != oldStat.st_mtime) {
		std::cout << "Reloading shaders!" << std::endl;
		delete shader;
		shader = new sf::Shader();
		shader->loadFromFile("res/shader/background.vert",
		                     "res/shader/background.frag");
	}

	oldStat = newStat;

	game->getTarget().setView(
	    sf::View(sf::FloatRect(0, 0, game->getTarget().getSize().x,
	                           game->getTarget().getSize().y)));
	block.setSize(sf::Vector2f(game->getTarget().getSize().x,
	                           game->getTarget().getSize().y));

	shader->setParameter("offset", offset.x, offset.y);
	game->getTarget().draw(block, shader);
}

void Background::update(Game *game) {
	// auto s = game->getTarget().getSize();
	// auto d = game->getDelta()*100;
	auto t = game->getTime() * 100 / 8.0;
	offset.x = t;
	offset.y = t;

	if (game->getActive() && sf::Keyboard::isKeyPressed(sf::Keyboard::F5)) {
		std::cout << "Reloading shaders!" << std::endl;
		delete shader;
		shader = new sf::Shader();
		shader->loadFromFile("res/shader/background.vert",
		                     "res/shader/background.frag");
	}
}

vector<Hitbox> Background::getHitboxes() const {
	return vector<Hitbox>();
}

double Background::getScale() const {
	return 1.0;
}

std::string Background::toString() const {
	return "Background";
}