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

	double getDelta() const;
	double getTime() const;
	bool getActive() const;

	sf::RenderWindow & getWindow();
	Resources & getResources();
	std::vector<Entity *> getEntities();

private:
	sf::RenderWindow window;
	std::vector<Entity *> entities;
	Resources resources;
	double delta;
	double time;
	sf::View renderView;
	bool windowActive;
	sf::RectangleShape blockedViews[4];

	void recalcView();
};

#endif
