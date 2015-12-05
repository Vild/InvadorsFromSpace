#ifndef RESOURCES_HPP_
#define RESOURCES_HPP_

#include <SFML/Graphics.hpp>

enum class Textures {
	Background = 0,
	Projectile,
	TestGuy,
	MrBob,

	NUM_OF_TEXTURES
};

class Resources {
public:
	Resources();
	~Resources();

	sf::Texture & getTexture(Textures id);

private:
	sf::Texture textures[static_cast<int>(Textures::NUM_OF_TEXTURES)];

	void load();
};

#endif