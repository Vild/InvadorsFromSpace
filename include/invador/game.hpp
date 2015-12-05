#ifndef GAME_HPP_
#define GAME_HPP_

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <invador/data.hpp>
#include <invador/resources.hpp>
class Entity;

class Game {
public:
	Game();
	~Game();

	int mainLoop();

	void addEntity(Entity * entity);

	double getDelta();
	double getTime();

	sf::RenderWindow & getWindow();
	Resources & getResources();

private:
	sf::RenderWindow window;
	std::vector<Entity *> entities;
	Resources resources;
	double delta;
	double time;
	sf::View renderView;

	void recalcView();
};

#endif
