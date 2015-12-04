#include <invador/game.hpp>

#include <invador/entity/projectile.hpp>
#include <invador/entity/testguy.hpp>

Game::Game() : window(sf::VideoMode(1000, 1000), "INVADORS FROM SPACE!"), renderView(sf::FloatRect(0, 0, 1000, 1000)) {
	window.setView(renderView);
	addEntity(new TestGuy(this, vec2(window.getSize().x/2, window.getSize().y/2)));
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

				double scalew = event.size.width / 1000.0;
				double scaleh = event.size.height / 1000.0;
				double scale = scalew < scaleh ? scalew : scaleh;

				//renderView.setZoom(scale);
				//renderView.setSize(event.size.width/**scale*/, event.size.height/**scale*/);
				renderView.setViewport(sf::FloatRect(0, 0, scale, scale));
				window.setView(renderView);
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