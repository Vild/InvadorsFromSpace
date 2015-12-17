#include <invador/game.hpp>

#include <invador/entity/projectile.hpp>
#include <invador/entity/background.hpp>
#include <invador/entity/missalice.hpp>
#include <invador/entity/mrbob.hpp>

#include <iostream>
#include <typeinfo>

Game::Game() : window(sf::VideoMode(1000, 1000), "INVADORS FROM SPACE!"), delta(0), time(0), windowActive(false),
	blockedViews({sf::RectangleShape(sf::Vector2f(0, 0)), sf::RectangleShape(sf::Vector2f(0, 0)), sf::RectangleShape(sf::Vector2f(0, 0)), sf::RectangleShape(sf::Vector2f(0, 0))}) {
	recalcView();
	addEntity(new Background(this));
	addEntity(new MissAlice(this, vec2(window.getSize().x/2, window.getSize().y/2)));
	addEntity(new MrBob(this, vec2(window.getSize().x/2, window.getSize().y/2)));

	blockedViews[0].setSize(sf::Vector2f(10000, 10000));
	blockedViews[0].setPosition(sf::Vector2f(-10000, 0));
	blockedViews[0].setFillColor(sf::Color(255, 255, 255, 255/4));

	blockedViews[1].setSize(sf::Vector2f(10000, 10000));
	blockedViews[1].setPosition(sf::Vector2f(1000, 0));
	blockedViews[1].setFillColor(sf::Color(255, 255, 255, 255/4));

	blockedViews[2].setSize(sf::Vector2f(10000, 10000));
	blockedViews[2].setPosition(sf::Vector2f(0, -10000));
	blockedViews[2].setFillColor(sf::Color(255, 255, 255, 255/4));

	blockedViews[3].setSize(sf::Vector2f(10000, 10000));
	blockedViews[3].setPosition(sf::Vector2f(0, 1000));
	blockedViews[3].setFillColor(sf::Color(255, 255, 255, 255/4));
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
			else if (event.type == sf::Event::Resized)
				recalcView();
			else if (event.type == sf::Event::GainedFocus)
				windowActive = true;
			else if (event.type == sf::Event::LostFocus)
				windowActive = false;
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

			vector<Hitbox> boxes = entities[i]->getHitboxes();
			for (unsigned int j = 0; j < boxes.size(); j++) {
				auto s = boxes[j].getSize();
				auto p = boxes[j].getOffset() + entities[i]->getPos() + entities[i]->getOffset();

				sf::RectangleShape box(sf::Vector2f(s.x, s.y));
				box.setPosition(sf::Vector2f(p.x, p.y));
				box.setFillColor(sf::Color::Transparent);
				box.setOutlineColor(sf::Color::Yellow);
				box.setOutlineThickness(2);
				window.draw(box);
			}
		}

		window.setView(renderView);
		for (int i = 0; i < 4; i++)
			window.draw(blockedViews[i]);

		window.display();
	}
	return 0;
}

void Game::addEntity(Entity * entity) {
	entities.push_back(entity);
}

double Game::getDelta() const {
	return delta;
}

double Game::getTime() const {
	return time;
}

bool Game::getActive() const {
	return windowActive;
}

sf::RenderWindow & Game::getWindow() {
	return window;
}

Resources & Game::getResources() {
	return resources;
}

std::vector<Entity *> Game::getEntities() {
	return entities;
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
