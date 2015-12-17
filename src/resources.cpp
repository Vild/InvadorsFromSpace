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
	textures[static_cast<int>(Textures::Background)].loadFromFile("res/img/background.png");
	textures[static_cast<int>(Textures::Projectile)].loadFromFile("res/img/projectile.png");
	textures[static_cast<int>(Textures::MissAlice)].loadFromFile("res/img/missalice.png");
	textures[static_cast<int>(Textures::MrBob)].loadFromFile("res/img/mrbob.png");
}