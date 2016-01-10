#include <invador/entity/projectile.hpp>
#include <invador/game.hpp>
#include <invador/entity/mrbob.hpp>

#include <iostream>

Projectile::Projectile(Game *game, vec2 pos, vec2 velocity, double rotate)
    : TexturedEntity(pos, game->getResources().getTexture(Textures::Projectile), 4),
      velocity(velocity), rotate(rotate), time(0) {
	pew.setBuffer(game->getResources().getPewBuffer());
	pew.setPitch((rotate == 0) ? 0.75 : 1);
	pew.setVolume((rotate == 0) ? 10 : 100);
	pew.play();
}

Projectile::~Projectile() {}

void Projectile::update(Game *game) {
	if (game->getActive()) {
		time += game->getDelta();
		setFrame((int)(time * 20) % 4 + ((int)rotate / 90) * 4);
		getPosRef() += velocity * game->getDelta();
		if (getPosRef().y < (int)(getTexture()->getSize().y * getScale()) / -2 ||
		    getPosRef().y > game->getTarget().getSize().y)
			getDeadRef() = true;

		auto myBoxes = getHitboxes();
		auto e = game->getEntities();
		for (unsigned int i = 0; i < e.size() && !getDeadRef(); i++) {
			if (e[i] != this) {
				auto boxes = e[i]->getHitboxes();

				for (unsigned int j = 0;  j < boxes.size() && !getDeadRef(); j++) {
					auto size = boxes[j].getSize();
					auto pos = boxes[j].getOffset() + e[i]->getPosRef() + e[i]->getOffsetRef();
					for (unsigned int k = 0; k < myBoxes.size() && !getDeadRef(); k++) {
						auto mySize = myBoxes[j].getSize();
						auto myPos = myBoxes[j].getOffset() + getPosRef() + getOffsetRef();

						if (pos + size >= myPos) {
							if (pos <= myPos + mySize) {
								std::cout << "Projectile hit: " << e[i]->toString() << std::endl;
								getDeadRef() = true;
								e[i]->getDeadRef() = true;
								if (dynamic_cast<MrBob *>( e[i]))
									game->setState(GameState::Lost);
							}
						}
					}
				}
			}
		}
	}
}

vector<Hitbox> Projectile::getHitboxes() const {
	if (((int)rotate / 90) % 2 == 0)
		return vector<Hitbox>(
		    {Hitbox(vec2(6 * getScale(), 2 * getScale()),
		            vec2(4 * getScale(), 12 * getScale()))});
	else
		return vector<Hitbox>(
		    {Hitbox(vec2(2 * getScale(), 6 * getScale()),
		            vec2(12 * getScale(), 4 * getScale()))});
}

double Projectile::getScale() const {
	return 1.5;
}

std::string Projectile::toString() const {
	return "Projectile";
}
