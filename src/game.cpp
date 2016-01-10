#include <invador/game.hpp>

#include <invador/entity/projectile.hpp>
#include <invador/entity/background.hpp>
#include <invador/entity/missalice.hpp>
#include <invador/entity/mrbob.hpp>

#include <iostream>
#include <typeinfo>
#include <cstdlib>
#include <ctime>

Game::Game()
    : window(sf::VideoMode(1000, 1000), "INVADORS FROM SPACE!"),
      currentTarget(&window), delta(0), time(0), windowActive(false),
      blockedViews({sf::RectangleShape(sf::Vector2f(0, 0)),
                    sf::RectangleShape(sf::Vector2f(0, 0)),
                    sf::RectangleShape(sf::Vector2f(0, 0)),
                    sf::RectangleShape(sf::Vector2f(0, 0))}),
      gameState(GameState::Intro) {

	std::srand(std::time(NULL));
	recalcView();
	addEntity(new Background(this));
	for (unsigned int x = 0; x < missAlicesColumn; x++)
		for (unsigned int y = 0; y < missAlicesRow; y++)
			missAlices[y * missAlicesColumn + x] = addEntity(new MissAlice(this, vec2((x + 1) * 64, y * 64 * 1.5), vec2(x, y)));

	addEntity(new MrBob(this, vec2(window.getSize().x / 2 - 32 * 10 / 2, 1000 - (80 * 3))));

	blockedViews[0].setSize(sf::Vector2f(10000, 10000));
	blockedViews[0].setPosition(sf::Vector2f(-10000, 0));
	blockedViews[0].setFillColor(sf::Color(25, 25, 25, 255));

	blockedViews[1].setSize(sf::Vector2f(10000, 10000));
	blockedViews[1].setPosition(sf::Vector2f(1000, 0));
	blockedViews[1].setFillColor(sf::Color(25, 25, 25, 255));

	blockedViews[2].setSize(sf::Vector2f(10000, 10000));
	blockedViews[2].setPosition(sf::Vector2f(0, -10000));
	blockedViews[2].setFillColor(sf::Color(25, 25, 25, 255));

	blockedViews[3].setSize(sf::Vector2f(10000, 10000));
	blockedViews[3].setPosition(sf::Vector2f(0, 1000));
	blockedViews[3].setFillColor(sf::Color(25, 25, 25, 255));

	protectiveSphere.setSize(sf::Vector2f(1000, 80 * 3));
	protectiveSphere.setPosition(sf::Vector2f(0, 1000 - (80 * 3)));
	protectiveSphere.setFillColor(sf::Color(50, 10, 100, 80));

	textBackground.setSize(sf::Vector2f(1000, 1000));
	textBackground.setFillColor(sf::Color(0, 0, 0, 200));

	font.loadFromFile("res/font/Orbitron-Black.ttf");

	introTitle.setFont(font);
	introTitle.setString("Invadors From SPACE!");
	introTitle.setCharacterSize(50);
	introTitle.setColor(sf::Color::Yellow);
	introTitle.setStyle(sf::Text::Bold);
	introTitle.setPosition(sf::Vector2f(1000 / 2 - introTitle.getGlobalBounds().width / 2, 100));

	introText.setFont(font);
	introText.setString(
		L"You are playing the character Bob.\n"
		"He lives on the planet D1-34-C.\n"
		"His planet has valuable minerals.\n"
		"\n"
		"One day the Alice army attacks to\n"
		"try to take over the planet\n"
		"Bob's goal is to keep them outside of\n"
		"the protective sphere.\n"
		"If he fails, he will lose the planet!\n"
		"\n"
		"To his disposal he has an old and\n"
		"slow anti-matter gun, disguised as\n"
		"a top hat.\n"
		"\n"
		"Good luck!\n"
		"\n"
		"Use the arrow keys or WASD to move and\n"
		"spacebar to shoot\n"
		"Press Enter to continue\n"
	);
	introText.setCharacterSize(40);
	introText.setColor(sf::Color::White);
	introText.setPosition(sf::Vector2f(1000 / 2 - introText.getGlobalBounds().width / 2, 100 + 50 * 2));

	lostTitle.setFont(font);
	lostTitle.setString("You lost to the attack :(");
	lostTitle.setCharacterSize(60);
	lostTitle.setColor(sf::Color::Red);
	lostTitle.setStyle(sf::Text::Bold);
	lostTitle.setPosition(sf::Vector2f(1000 / 2 - lostTitle.getGlobalBounds().width / 2, 1000 / 2 - lostTitle.getGlobalBounds().height / 2 - 100));

	lostText.setFont(font);
	lostText.setString(L"Press enter to play again!");
	lostText.setCharacterSize(40);
	lostText.setColor(sf::Color::White);
	lostText.setPosition(sf::Vector2f(1000 / 2 - lostText.getGlobalBounds().width / 2, 1000 / 2 - lostText.getGlobalBounds().height / 2));

	wonTitle.setFont(font);
	wonTitle.setString("Congrats, You Won!");
	wonTitle.setCharacterSize(60);
	wonTitle.setColor(sf::Color::Green);
	wonTitle.setStyle(sf::Text::Bold);
	wonTitle.setPosition(sf::Vector2f(1000 / 2 - wonTitle.getGlobalBounds().width / 2, 1000 / 2 - wonTitle.getGlobalBounds().height / 2 - 100));

	wonText.setFont(font);
	wonText.setString(L"Press enter to play again!");
	wonText.setCharacterSize(40);
	wonText.setColor(sf::Color::White);
	wonText.setPosition(sf::Vector2f(1000 / 2 - wonText.getGlobalBounds().width / 2, 1000 / 2 - wonText.getGlobalBounds().height / 2));

}

Game::~Game() {
	for (unsigned int i = 0; i < entities.size(); i++)
		delete entities[i];
	entities.clear();
}

int Game::mainLoop() {
	sf::Clock clock;
	double fpsTime = 0;
	int fps = 0;
	while (window.isOpen()) {
		sf::Time elapsed = clock.restart();
		delta = elapsed.asSeconds();
		time += delta;
		fpsTime += delta;

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::Resized)
				recalcView();
			else if (event.type == sf::Event::GainedFocus)
				windowActive = true;
			else if (event.type == sf::Event::LostFocus)
				windowActive = false;
			else if (event.type == sf::Event::KeyReleased) {
				if (event.key.code == sf::Keyboard::Escape)
					window.close();

				else if (event.key.code == sf::Keyboard::F10)
						gameState = GameState::Won;

				else if (event.key.code == sf::Keyboard::Return) {
					if (gameState == GameState::Intro)
						gameState = GameState::Game;

					if (gameState == GameState::Lost || gameState == GameState::Won) {
						gameState = GameState::Intro;
						delta = 0;
						for (unsigned int i = 0; i < entities.size(); i++)
							delete entities[i];
						entities.clear();

						addEntity(new Background(this));
						for (unsigned int x = 0; x < missAlicesColumn; x++)
							for (unsigned int y = 0; y < missAlicesRow; y++)
								missAlices[y * missAlicesColumn + x] = addEntity(new MissAlice(this, vec2((x + 1) * 64, y * 64 * 1.5), vec2(x, y)));

						addEntity(new MrBob(this, vec2(window.getSize().x / 2 - 32 * 10 / 2, 1000 - (80 * 3))));
					}
				}

			}
		}


		for (unsigned int i = 0; i < entities.size(); i++) {
			entities[i]->update(this);
			if (entities[i]->getDeadRef()) {
				for (int j = 0; j < missAlicesColumn * missAlicesRow; j++)
					if (missAlices[j] == entities[i])
						missAlices[j] = NULL;

				delete entities[i];
				entities.erase(entities.begin() + i);
				i--;
			}
		}

		window.clear(sf::Color(0, 0, 0, 255));
		window.draw(protectiveSphere);

		for (unsigned int i = 0; i < entities.size(); i++) {
			window.setView(renderView);
			entities[i]->render(this);

			// Uncomment to enable drawing of hitboxes
			/*vector<Hitbox> boxes = entities[i]->getHitboxes();
			for (unsigned int j = 0; j < boxes.size(); j++) {
				auto s = boxes[j].getSize();
				auto p = boxes[j].getOffset() + entities[i]->getPosRef() + entities[i]->getOffsetRef();

				sf::RectangleShape box(sf::Vector2f(s.x, s.y));
				box.setPosition(sf::Vector2f(p.x, p.y));
				box.setFillColor(sf::Color::Transparent);
				box.setOutlineColor(sf::Color::Yellow);
				box.setOutlineThickness(2);
				 window.draw(box);
			}*/
		}

		window.setView(renderView);
		if (gameState == GameState::Game) {
			bool noMoreAlice = true;
			for (int i = 0; i < missAlicesColumn * missAlicesRow && noMoreAlice; i++)
				if (missAlices[i])
					noMoreAlice = false;

			if (noMoreAlice) {
				gameState = GameState::Won;
			}
		} else {
			window.draw(textBackground);
			if (gameState == GameState::Intro) {
				window.draw(introTitle);
				window.draw(introText);
			} else if (gameState == GameState::Lost) {
				window.draw(lostTitle);
				window.draw(lostText);
			} else/* if (gameState == GameState::Won) */{
				window.draw(wonTitle);
				window.draw(wonText);
			}
		}

		for (int i = 0; i < 4; i++)
			window.draw(blockedViews[i]);

		window.display();
		fps++;

		if (fpsTime >= 0.5) {
			std::cout << "FPS: " << fps * 2 << std::endl;
			fps = 0;
			fpsTime -= 0.5;
		}
	}
	return 0;
}

Entity *Game::addEntity(Entity *entity) {
	entities.push_back(entity);
	return entity;
}

double Game::getDelta() const {
	return delta;
}

double Game::getTime() const {
	return time;
}

bool Game::getActive() const {
	return windowActive && gameState == GameState::Game;
}

sf::RenderWindow &Game::getWindow() {
	return window;
}

sf::RenderTarget &Game::getTarget() {
	return *currentTarget;
}

Resources &Game::getResources() {
	return resources;
}

std::vector<Entity *> Game::getEntities() {
	return entities;
}

Entity *Game::getMissAlices(vec2 pos) {
	if (pos.x >= 0 && pos.x < missAlicesColumn && pos.y >= 0 && pos.y < missAlicesRow)
		return missAlices[(int)pos.y * missAlicesColumn + (int)pos.x];
	return NULL;
}

void Game::setState(GameState state) {
	gameState = state;
}

void Game::recalcView() {
	int newW = (1000 * window.getSize().x) / window.getSize().y;
	int newH = (1000 * window.getSize().y) / window.getSize().x;
	int displaceW = (newW - 1000) / (-2);
	int displaceH = (newH - 1000) / (-2);

	if (displaceW < displaceH)
		renderView = sf::View(sf::FloatRect(displaceW, 0, newW, 1000));
	else
		renderView = sf::View(sf::FloatRect(0, displaceH, 1000, newH));
}
