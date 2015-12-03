#include <invador/game.hpp>

#include <invador/entity/projectile.hpp>
#include <invador/entity/mrpop.hpp>

Game::Game() : window(sf::VideoMode(1000, 1000), "INVADORS FROM SPACE!") {
	addEntity(new MrPop(this, vec2(window.getSize().x/2, window.getSize().y/2)));
}

Game::~Game() {
	for (unsigned int i = 0; i < entities.size(); i++)
		delete entities[i];
}

int Game::mainLoop() {
	sf::Clock clock;

	window.setView(sf::View(sf::FloatRect(0, 0, 1000, 1000)));
	while (window.isOpen()) {
		sf::Time elapsed = clock.restart();
		delta = elapsed.asSeconds();
		time += delta;

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::Resized)
				window.setView(sf::View(sf::FloatRect(0, 0, 1000, 1000)));
		}

		for (unsigned int i = 0; i < entities.size(); i++) {
			entities[i]->update(this);
			if (entities[i]->getDead()) {
				delete entities[i];
				entities.erase(entities.begin() + i);
				i--;
			}
		}

		window.clear(sf::Color(25, 80, 25, 255));
		for (unsigned int i = 0; i < entities.size(); i++)
			entities[i]->render(this);
		window.display();
	}
	return 0;
}

void Game::addEntity(Entity * entity) {
	entities.push_back(entity);
}

double Game::getDelta() {
	return delta;
}

double Game::getTime() {
	return time;
}

sf::RenderWindow & Game::getWindow() {
	return window;
}

Resources & Game::getResources() {
	return resources;
}