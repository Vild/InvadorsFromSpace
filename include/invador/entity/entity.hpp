#ifndef ENTITY_HPP_
#define ENTITY_HPP_

#include <string>
#include <invador/data.hpp>
#include <invador/hitbox.hpp>
#include <SFML/Graphics.hpp>
class Game; // Can't include Game.hpp here because game.hpp includes this file

class Entity {
public:
	Entity(vec2 pos);
	virtual ~Entity();

	virtual void render(Game *game) = 0;
	virtual void update(Game *game) = 0;

	bool isHit(vec2 pos);
	virtual vector<Hitbox> getHitboxes() const = 0;

	bool &getDeadRef();
	vec2 &getPosRef();
	vec2 &getOffsetRef();

	virtual std::string toString() const = 0;

private:
	bool dead;
	vec2 pos;
	vec2 offset;
};

#include <invador/game.hpp>

#endif
