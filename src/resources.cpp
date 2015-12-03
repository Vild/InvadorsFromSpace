#include <invador/resources.hpp>

Resources::Resources() {
	load();
}
Resources::~Resources() {

}

sf::Texture & Resources::getTexture(Textures id) {
	return textures[static_cast<int>(id)];
}

void Resources::load() {
	textures[static_cast<int>(Textures::PROJECTILE)].loadFromFile("res/img/projectile.png");
	textures[static_cast<int>(Textures::MRPOP)].loadFromFile("res/img/mrpop.png");
}