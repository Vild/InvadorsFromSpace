#include <invador/entity/projectile.hpp>
#include <invador/game.hpp>

#include <iostream>

Projectile::Projectile(Game * game, vec2 pos, vec2 velocity, double rotate) : TexturedEntity(pos, game->getResources().getTexture(Textures::Projectile), 4), velocity(velocity), rotate(rotate) {
}

Projectile::~Projectile() {
}

void Projectile::update(Game * game) {
	setFrame((int)(game->getTime()*20) % 4 +((int)rotate / 90)*4);
	getPos() += velocity * game->getDelta();
	if (getPos().y < (int)(getTexture()->getSize().y*getScale()) / -2 ||
			getPos().y > game->getTarget().getSize().y)
		getDead() = true;

	auto myBoxes = getHitboxes();
	auto e = game->getEntities();
	for (unsigned int i = 0; i < e.size() && !getDead(); i++) {
		if (e[i] != this) {
			auto boxes = e[i]->getHitboxes();

			for (unsigned int j = 0; j < boxes.size() && !getDead(); j++) {
				auto size = boxes[j].getSize();
				auto pos = boxes[j].getOffset() + e[i]->getPos() + e[i]->getOffset();
				for (unsigned int k = 0; k < myBoxes.size() && !getDead(); k++) {
					auto mySize = myBoxes[j].getSize();
					auto myPos = myBoxes[j].getOffset() + getPos() + getOffset();

					if (pos + size >= myPos) {
						if (pos <= myPos + mySize) {
							std::cout << "Projectile hit: " << e[i]->toString() << std::endl;
							getDead() = true;
							e[i]->getDead() = true;
						}
					}
				}
			}
		}
	}
}

vector<Hitbox> Projectile::getHitboxes() const {
	if (((int)rotate / 90) % 2 == 0)
		return vector<Hitbox>({Hitbox(vec2(6*getScale(), 2*getScale()), vec2(4*getScale(), 12*getScale()))});
	else
		return vector<Hitbox>({Hitbox(vec2(2*getScale(), 6*getScale()), vec2(12*getScale(), 4*getScale()))});
}

double Projectile::getScale() const {
	return 1.5;
}

std::string Projectile::toString() const {
	return "Projectile";
}
