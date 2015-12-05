#include <invador/game.hpp>

#include <invador/entity/projectile.hpp>
#include <invador/entity/background.hpp>
#include <invador/entity/testguy.hpp>
#include <invador/entity/mrbob.hpp>

Game::Game() : window(sf::VideoMode(1000, 1000), "INVADORS FROM SPACE!"), delta(0), time(0) {
	recalcView();
	addEntity(new Background(this));
	addEntity(new TestGuy(this, vec2(window.getSize().x/2, window.getSize().y/2)));
	addEntity(new MrBob(this, vec2(window.getSize().x/2, window.getSize().y/2)));
}

Game::~Game() {
	for (unsigned int i = 0; i < entities.size(); i++)
		delete entities[i];
}

int Game::mainLoop() {
	sf::Clock clock;

	while (window.isOpen()) {
		sf::Time elapsed = clock.restart();
		delta = elapsed.asSeconds();
		time += delta;

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::Resized) {
				recalcView();
			}
		}

		for (unsigned int i = 0; i < entities.size(); i++) {
			entities[i]->update(this);
			if (entities[i]->getDead()) {
				delete entities[i];
				entities.erase(entities.begin() + i);
				i--;
			}
		}

		window.clear(sf::Color(0, 0, 0, 255));
		for (unsigned int i = 0; i < entities.size(); i++) {
			window.setView(renderView);
			entities[i]->render(this);
		}

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

void Game::recalcView() {
	int newW = (1000*window.getSize().x)/window.getSize().y;
	int newH = (1000*window.getSize().y)/window.getSize().x;
	int displaceW = (newW - 1000)/(-2);
	int displaceH = (newH - 1000)/(-2);
	if (displaceW < displaceH)
		renderView = sf::View(sf::FloatRect(displaceW, 0, newW, 1000));
	else
		renderView = sf::View(sf::FloatRect(0, displaceH, 1000, newH));
}