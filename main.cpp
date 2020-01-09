#include <SFML/System.hpp>
#include "Entity.h"
#include <time.h>
#include "Asteroid.h"
#include "Bullet.h"
#include "Player.h"

using namespace sf;

//const int W = 1200;
//const int H = 800;

bool isCollide(Entity* a, Entity* b)
{
	return (b->getX() - a->getX()) * (b->getX() - a->getX()) +
		(b->getY() - a->getY()) * (b->getY() - a->getY()) <
		(a->getR() + b->getR()) * (a->getR() + b->getR());
}

int main()
{
	srand(time(0));

	RenderWindow app(VideoMode(W, H), "Asteroids!");
	app.setFramerateLimit(45);

	Texture tSpaceShip, tBackground, tExplosion, tAsteroid, tFireBullet, tLittleAsteroid, tExplosion2;
	tSpaceShip.loadFromFile("images/White_Ship_Space.png");
	tBackground.loadFromFile("images/back1.jpg");
	tExplosion.loadFromFile("images/explosions/type_C.png");
	tAsteroid.loadFromFile("images/rock.png");
	tFireBullet.loadFromFile("images/fire_blue.png");
	tLittleAsteroid.loadFromFile("images/rock_small.png");
	tExplosion2.loadFromFile("images/explosions/type_B.png");

	tSpaceShip.setSmooth(true);
	tBackground.setSmooth(true);

	Sprite background(tBackground);

	Animation sExplosion(tExplosion, 0, 0, 256, 256, 48, 0.5);
	Animation sRock(tAsteroid, 0, 0, 64, 64, 16, 0.2);
	Animation sRock_small(tLittleAsteroid, 0, 0, 64, 64, 16, 0.2);
	Animation sBullet(tFireBullet, 0, 0, 32, 64, 16, 0.8);
	Animation sPlayer(tSpaceShip, 0, 0, 31, 31, 1, 0);
	Animation sExplosion_ship(tExplosion2, 0, 0, 192, 192, 64, 0.5);

	Font font;
	font.loadFromFile("fonts/cour.ttf");
	Text text("POINTS: 0", font, 32);
	//text.setColor(Color::White);
	text.setStyle(sf::Text::Bold | sf::Text::Underlined);
	text.setPosition(10, 10);

	std::list<Entity*> entities;

	for (int i = 0; i < 15; i++)
	{
		Asteroid* a = new Asteroid();
		a->settings(sRock, rand() % W, rand() % H, rand() % 360, 25);
		entities.push_back(a);
	}

	Player* p = new Player();
	p->settings(sPlayer, W / 2, H / 2, 270, 20);
	entities.push_back(p);

	//MAIN
	while (app.isOpen())
	{
		Event event;
		while (app.pollEvent(event))
		{
			if (event.type == Event::Closed)
				app.close();

			if (event.type == Event::KeyPressed)
				if (event.key.code == Keyboard::Space)
				{
					Bullet* b = new Bullet();
					b->settings(sBullet, p->getX(), p->getY(), p->getAngle(), 10);
					entities.push_back(b);
				}
		}

		if (Keyboard::isKeyPressed(Keyboard::Right)) p->setAngle(p->getAngle() + 3);
		if (Keyboard::isKeyPressed(Keyboard::Left))  p->setAngle(p->getAngle() - 3);
		if (Keyboard::isKeyPressed(Keyboard::Up)) p->setThrust(true);
		else p->setThrust(false);

		for (auto a : entities)
			for (auto b : entities)
			{
				//KILLED ASTEROID
				if (a->getName() == "asteroid" && b->getName() == "bullet")
					if (isCollide(a, b))
					{
						a->setLife(false);
						b->setLife(false);

						Entity* e = new Entity();
						e->settings(sExplosion, a->getX(), a->getY());
						e->setName("explosion");
						entities.push_back(e);

						if (a->getR() == 15) {
							//little rock
							p->setScore(p->getScore() + 50 + rand() % 25);
							text.setString("POINTS: " + std::to_string(p->getScore()));
						}

						for (int i = 0; i < 2; i++)
						{
							if (a->getR() == 15) continue;
							Entity* e = new Asteroid();
							e->settings(sRock_small, a->getX(), a->getY(), rand() % 360, 15);
							entities.push_back(e);
						}

					}

				//DEAD SHIP
				if (a->getName() == "player" && b->getName() == "asteroid")
					if (isCollide(a, b))
					{
						b->setLife(false);
						//playerLife--

						Entity* e = new Entity();
						e->settings(sExplosion_ship, a->getX(), a->getY());
						e->setName("explosion");
						entities.push_back(e);

						p->settings(sPlayer, W / 2, H / 2, 270, 20);
						p->setDx(0); p->setDy(0);
					}
			}

		p->setAnim(sPlayer);

		for (auto e : entities)
			if (e->getName() == "explosion")
				if (e->animIsEnd()) e->setLife(0);

		//сделать ограничение на создание астероидов, лул
		if (rand() % 150 == 0)
		{
			Asteroid* a = new Asteroid();
			a->settings(sRock, 0, rand() % H, rand() % 360, 25);
			entities.push_back(a);
		}

		for (auto i = entities.begin(); i != entities.end();)
		{
			Entity* e = *i;

			e->update();

			if (e->getLife() == false) { i = entities.erase(i); delete e; }
			else i++;
		}

		//drawed picture
		app.draw(background);
		for (auto i : entities) i->draw(app);
		app.draw(text);
		app.display();
	}

	return 0;
}
