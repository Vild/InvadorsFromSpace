#ifndef TEXTUREDENITITY_HPP_
#define TEXTUREDENITITY_HPP_

#include <invador/entity/entity.hpp>
#include <invador/game.hpp>
#include <SFML/Graphics.hpp>

class TexturedEntity : public Entity {
public:
	TexturedEntity(vec2 pos, sf::Texture &texture, int textureGrid);
	virtual ~TexturedEntity();

	virtual void render(Game *game);

	void setFrame(int index);

	sf::Texture *getTexture();
	sf::Sprite &getSprite();
	virtual double getScale() const;

private:
	sf::Texture *texture;
	sf::Sprite sprite;
	int textureGrid;
};

#endif
