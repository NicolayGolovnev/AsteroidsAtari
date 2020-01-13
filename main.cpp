#include <SFML/System.hpp>
#include "Entity.h"
#include <time.h>
#include "Asteroid.h"
#include "Bullet.h"
#include "Player.h"

#include <iostream>

#define MAX_ASTEROIDS 9
#define MAX_BULLETS 15

using namespace sf;

/*
ADDED-LIST:
DONE	- LIFES
MB	- PICTURE LIFE AND Outing that
	- RECORDs TABLE
DONE	- INVULNERABILITY ON START BEFORE MOVING
	- PLAY TIME
*/

//const int W = 1200;
//const int H = 800;

int lifes = 3;
bool invulabe = true;

bool isCollide(Entity* a, Entity* b)
{
	return (b->getX() - a->getX()) * (b->getX() - a->getX()) +
		(b->getY() - a->getY()) * (b->getY() - a->getY()) <
		(a->getR() + b->getR()) * (a->getR() + b->getR());
}

int main()
{
	srand(time(0));
	Clock clock, clockPause;
	bool enableOnce = true;

	RenderWindow app(VideoMode(W, H), "Asteroids!");
	app.setFramerateLimit(45);

	Texture tSpaceShip, tBackground, tExplosion, tAsteroid, tFireBulletBlue, tFireBulletRed, tLittleAsteroid, tExplosion2;
	tSpaceShip.loadFromFile("images/White_Ship_Space.png");
	tBackground.loadFromFile("images/back1.jpg");
	tExplosion.loadFromFile("images/explosions/type_C.png");
	tAsteroid.loadFromFile("images/rock.png");
	tFireBulletBlue.loadFromFile("images/fire_blue.png");
	tFireBulletRed.loadFromFile("images/fire_red.png");
	tLittleAsteroid.loadFromFile("images/rock_small.png");
	tExplosion2.loadFromFile("images/explosions/type_B.png");

	tSpaceShip.setSmooth(true);
	tBackground.setSmooth(true);

	Sprite background(tBackground);

	Animation sExplosion(tExplosion, 0, 0, 256, 256, 48, 0.5);
	Animation sRock(tAsteroid, 0, 0, 64, 64, 16, 0.2);
	Animation sRock_small(tLittleAsteroid, 0, 0, 64, 64, 16, 0.2);
	Animation sBullet(tFireBulletBlue, 0, 0, 32, 64, 16, 0.8);
	Animation sPlayer(tSpaceShip, 0, 0, 64, 64, 1, 0);
	Animation sExplosion_ship(tExplosion2, 0, 0, 192, 192, 64, 0.5);

	Font font;
	font.loadFromFile("fonts/cour.ttf");

	//��� ��� ����� � ��� ����� ����
	Texture tbackgroundPause;
	tbackgroundPause.loadFromFile("images/blackBackground.jpg");
	Sprite backgroundPause(tbackgroundPause);

	//������ ��� ���������
	Text gameOver("GAME OVER", font, 64);
	gameOver.setStyle(Text::Bold);
	gameOver.setPosition(W / 2 - 150, 200);

	Text pressForExit("PRESS Y FOR EXIT", font, 32);
	pressForExit.setStyle(Text::Bold);
	pressForExit.setPosition(W / 2 - 135, 350);

	//������-���������� ��� ����
	Text point("POINTS: 0", font, 32);
	point.setStyle(sf::Text::Bold | sf::Text::Underlined);
	point.setPosition(10, 10);

	Text time("TIME: 0", font, 32);
	time.setStyle(sf::Text::Bold | sf::Text::Underlined);
	time.setPosition(10, 44);

	Text life("LIFES: 3", font, 32);
	life.setStyle(sf::Text::Bold | sf::Text::Underlined);
	life.setPosition(W - 175, 10);

	std::list<Entity*> entities;
//-------------------------------//CREATE A ASTEROID WITH THE PLAYER//------------------------------------------//
	int countAsteroids = 0;
	for (int i = 0; i < MAX_ASTEROIDS; i++)
	{
		Asteroid* a = new Asteroid();
		a->settings(sRock, rand() % W, rand() % H, rand() % 360, 25);
		entities.push_back(a);
		countAsteroids++;
	}

	Player* p = new Player();
	p->settings(sPlayer, W / 2, H / 2, 270, 20);
	entities.push_back(p);
	int counterTime = 0, timeCreateAsteroids = 0, counterBullets = 0;
	int gameTime = 0;

	//ESC - PAUSE - �� ������ ����� ������ ������ �����
	Text pause("ESC - PAUSE", font, 16);
	pause.setPosition(W / 2 - 120, H - 18);
//----------------------------------------//MAIN//------------------------------------------------//
	while (app.isOpen())
	{
		
		float time� = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time� /= 800;
		//std::cout << time� << std::endl;
		
		Event event;
		while (app.pollEvent(event))
		{
			if (event.type == Event::Closed)
				app.close();
//---------------------------------------------//PAUSE//------------------------------------------//
			if (event.type == Event::KeyPressed) {
				if (event.key.code == Keyboard::Escape) {
					//TAKE A PAUSE
					bool pause = true;
					invulabe = true;
					enableOnce = false;
					clockPause.restart();

					//���������� ���� ��������, ������� ����� ���� ����������
					backgroundPause.setColor(Color(255, 255, 255, 170));
					app.draw(backgroundPause);
					//FAQ and By Author

					app.display();
					int count = 0, countM = 0;
					while (pause)
						if (Keyboard::isKeyPressed(Keyboard::Q))
							pause = false;
				}
//--------------------------------------------//CREATE BULLET//-----------------------------------//
				if (event.key.code == Keyboard::Space){
					enableOnce = true;
					if (counterBullets < MAX_BULLETS) {
						Bullet* b = new Bullet();
						b->settings(sBullet, p->getX(), p->getY(), p->getAngle(), 10);
						entities.push_back(b);
						counterBullets++;
					}
				}

				if (event.type == Event::KeyReleased) {
					if (event.key.code == Keyboard::Escape)
						enableOnce = true;
				}

				
			}
		}

		counterTime += time�;
		if (counterTime > 1000) {
			timeCreateAsteroids++;
			gameTime++;
			time.setString("TIME: " + std::to_string(gameTime));
			//enableOnce = true;
			counterTime = 0;
		}
//---------------------------------------------//INVULABE, KEYS//----------------------------------------//
		if (invulabe) {
			if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::Left) ||
				Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::Space))
				invulabe = false;
		}

		if (Keyboard::isKeyPressed(Keyboard::Right)) p->setAngle(p->getAngle() + 3);
		if (Keyboard::isKeyPressed(Keyboard::Left))  p->setAngle(p->getAngle() - 3);
		if (Keyboard::isKeyPressed(Keyboard::Up)) p->setThrust(true);
		else p->setThrust(false);

		for (auto a : entities)
			for (auto b : entities)
			{
//-----------------------------------------//KILLED ASTEROID//-----------------------------------------------//
				if (a->getName() == "asteroid" && b->getName() == "bullet")
					if (isCollide(a, b))
					{
						a->setLife(false);
						b->setLife(false);
						countAsteroids--;

						Entity* e = new Entity();
						e->settings(sExplosion, a->getX(), a->getY());
						e->setName("explosion");
						entities.push_back(e);

						if (a->getR() == 15) {
							//little rock
							p->setScore(p->getScore() + 50 + rand() % 25);
							point.setString("POINTS: " + std::to_string(p->getScore()));
						}

						for (int i = 0; i < 2; i++)
						{
							if (a->getR() == 15) continue;
							Entity* e = new Asteroid();
							e->settings(sRock_small, a->getX(), a->getY(), rand() % 360, 15);
							entities.push_back(e);
						}
					}

//--------------------------------------------//DEAD SHIP, GAME OVER//------------------------------------------//
				if (a->getName() == "player" && b->getName() == "asteroid")
					if (!invulabe)
						if (isCollide(a, b)) {
							b->setLife(false);
							lifes--;
							life.setString("LIFE: " + std::to_string(lifes));
							invulabe = true;

//---------------------------------------------------//GAME OVER//-------------------------------------------//
							if (lifes == 0) {
								//����� ������� ���� � �������
								backgroundPause.setColor(Color(255, 255, 255, 210));
								life.setString("LIFE: 0");
								app.draw(backgroundPause);
								app.draw(life);
								app.draw(point);
								app.draw(time);

								app.draw(gameOver);
								app.draw(pressForExit);
								app.display();

								while (app.isOpen()) {
									while (app.pollEvent(event))
										if (event.type == Event::Closed)
											app.close();

									if (Keyboard::isKeyPressed(Keyboard::Y))
										app.close();
								}
							}

							Entity* e = new Entity();
							e->settings(sExplosion_ship, a->getX(), a->getY());
							e->setName("explosion");
							entities.push_back(e);

							p->settings(sPlayer, W / 2, H / 2, 270, 20);
							p->setDx(0); p->setDy(0);
					}
						}

		for (auto e : entities)
			if (e->getName() == "explosion")
				if (e->animIsEnd()) e->setLife(0);

		//�������� ����� ����������, ����� ��� �����
		if (timeCreateAsteroids == 5) {
			timeCreateAsteroids = 0;
			if (countAsteroids < MAX_ASTEROIDS) {
				Asteroid* a = new Asteroid();
				a->settings(sRock, 0, rand() % H, rand() % 360, 25);
				entities.push_back(a);
			}
		}
		//���������� �������� ���� ��������, ������� ��������
		//�������� "�������" ��������
		for (auto i = entities.begin(); i != entities.end();)
		{
			Entity* e = *i;

			e->update();

			if (e->getLife() == false) {
				if (e->getName() == "bullet")
					counterBullets--;
				i = entities.erase(i);
				delete e; 
			}
			else i++;
		}

//-------------------------------------//��������� ��������//-----------------------------------------//
		app.draw(background);
		p->setAnim(sPlayer);
		for (auto i : entities) i->draw(app);
		app.draw(point);
		app.draw(life);
		app.draw(time);
		app.draw(pause);
		app.display();
	}

	return 0;
}
