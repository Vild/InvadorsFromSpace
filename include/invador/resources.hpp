#ifndef RESOURCES_HPP_
#define RESOURCES_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

enum class Textures {
	Projectile = 0,
	MissAlice,
	MrBob,

	NUM_OF_TEXTURES
};

class Resources {
public:
	Resources();
	~Resources();

	sf::Texture &getTexture(Textures id);
	sf::SoundBuffer &getPewBuffer();

private:
	sf::Texture textures[static_cast<int>(Textures::NUM_OF_TEXTURES)];
	sf::SoundBuffer pewBuffer;

	void load();
};

#endif