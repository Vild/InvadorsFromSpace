#ifndef ENTITY_HPP_
#define ENTITY_HPP_

#include <string>
#include <invador/data.hpp>
#include <SFML/Graphics.hpp>
class Game;

class Entity {
public:
	Entity(sf::Texture & texture, vec2 pos, int textureGrid);
	virtual ~Entity();

	void setFrame(int index);

	virtual void render(Game * game);
	virtual void update(Game * game) = 0;

	virtual bool isHit(vec2 pos) = 0;

	bool & getDead();
	vec2 & getPos();
	vec2 & getOffset();

	sf::Texture & getTexture();
	sf::Sprite & getSprite();
private:
	bool dead;
	vec2 pos;
	vec2 offset;
	sf::Texture & texture;
	sf::Sprite sprite;
	int textureGrid;
};

#endif
