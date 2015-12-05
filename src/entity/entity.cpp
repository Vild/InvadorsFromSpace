#include <invador/entity/entity.hpp>
#include <assert.h>
#include <invador/game.hpp>

Entity::Entity(sf::Texture & texture, vec2 pos, int textureGrid) : dead(false), pos(pos), offset(0, 0), texture(texture), textureGrid(textureGrid) {
	texture.setSmooth(false);
	sprite.setTexture(texture);
	sprite.setScale(sf::Vector2f(getScale(), getScale()));
	setFrame(0);
}

Entity::~Entity() {}

void Entity::setFrame(int index) {
	auto s = texture.getSize();
	sf::IntRect rect;
	rect.left = (index % textureGrid) * (s.x / textureGrid);
	rect.top = (index / textureGrid) * (s.y / textureGrid);
	rect.width = s.x / textureGrid;
	rect.height = s.y / textureGrid;
	sprite.setTextureRect(rect);
}

void Entity::render(Game * game) {
	assert(sprite.getTexture());
	vec2 p = pos + offset;
	sprite.setPosition(p.x, p.y);
	game->getWindow().draw(sprite);
}

bool & Entity::getDead() {
	return dead;
}

vec2 & Entity::getPos() {
	return pos;
}

vec2 & Entity::getOffset() {
	return offset;
}

sf::Texture & Entity::getTexture() {
	return texture;
}

sf::Sprite & Entity::getSprite() {
	return sprite;
}

double Entity::getScale() const {
	return 10.0;
}