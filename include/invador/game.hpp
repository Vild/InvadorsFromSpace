#ifndef GAME_HPP_
#define GAME_HPP_

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <invador/data.hpp>
#include <invador/resources.hpp>
class Entity;

enum class GameState {
	Intro,
	Game,
	Lost,
	Won
};

class Game {
public:
	Game();
	~Game();

	int mainLoop();

	Entity *addEntity(Entity *entity);

	double getDelta() const;
	double getTime() const;
	bool getActive() const;

	sf::RenderWindow &getWindow();
	sf::RenderTarget &getTarget();
	Resources &getResources();
	std::vector<Entity *> getEntities();
	Entity *getMissAlices(vec2 pos);

	void setState(GameState state);

private:
	const static int missAlicesRow = 6;
	const static int missAlicesColumn = 14;
	sf::RenderWindow window;
	sf::RenderTarget *currentTarget;
	std::vector<Entity *> entities;
	Entity *missAlices[missAlicesColumn * missAlicesRow];
	Resources resources;
	double delta;
	double time;
	sf::View renderView;
	bool windowActive;
	sf::RectangleShape blockedViews[4];
	GameState gameState;

	sf::RectangleShape protectiveSphere;

	sf::RectangleShape textBackground;
	sf::Font font;

	sf::Text introTitle;
	sf::Text introText;

	sf::Text lostTitle;
	sf::Text lostText;

	sf::Text wonTitle;
	sf::Text wonText;

	void recalcView();
};

#endif
