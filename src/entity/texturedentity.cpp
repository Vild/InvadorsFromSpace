#include <invador/entity/texturedentity.hpp>

TexturedEntity::TexturedEntity(vec2 pos, sf::Texture & texture, int textureGrid) : Entity(pos), texture(&texture), textureGrid(textureGrid) {
	this->texture->setSmooth(false);
	sprite.setTexture(texture);
	sprite.setScale(sf::Vector2f(getScale(), getScale()));
	setFrame(0);
}

TexturedEntity::~TexturedEntity() {
}

void TexturedEntity::setFrame(int index) {
	auto s = texture->getSize();
	sf::IntRect rect;
	rect.left = (index % textureGrid) * (s.x / textureGrid);
	rect.top = (index / textureGrid) * (s.y / textureGrid);
	rect.width = s.x / textureGrid;
	rect.height = s.y / textureGrid;
	sprite.setTextureRect(rect);
}

void TexturedEntity::render(Game * game) {
	vec2 p = getPos() + getOffset();
	sprite.setPosition(p.x, p.y);
	game->getWindow().draw(sprite);
}

sf::Texture * TexturedEntity::getTexture() {
	return texture;
}

sf::Sprite & TexturedEntity::getSprite() {
	return sprite;
}

double TexturedEntity::getScale() const {
	return 3.0;//5.0;
}
