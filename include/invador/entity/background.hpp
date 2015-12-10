#ifndef BACKGROUND_HPP_
#define BACKGROUND_HPP_

#include <invador/entity/entity.hpp>

class Background : public Entity {
public:
	Background(Game * game);
	virtual ~Background();

	void render(Game * game);
	void update(Game * game);
	bool isHit(vec2 pos);
	double getScale() const;

	vector<Hitbox> getHitboxes() const;

	virtual std::string toString() const;
private:
	sf::RectangleShape block;
	sf::Shader * shader;
	vec2 offset;
};

#endif
