#ifndef PROJECTILE_HPP_
#define PROJECTILE_HPP_

#include <invador/entity/texturedentity.hpp>
#include <SFML/Audio.hpp>

class Projectile : public TexturedEntity {
public:
	Projectile(Game *game, vec2 pos, vec2 velocity, double rotate);
	virtual ~Projectile();

	void update(Game *game);
	vector<Hitbox> getHitboxes() const;
	virtual double getScale() const;

	virtual std::string toString() const;

private:
	vec2 velocity;
	double rotate;
	double time;
	sf::Sound pew;
};

#endif
