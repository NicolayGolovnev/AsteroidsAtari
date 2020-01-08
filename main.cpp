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

	Event newEvent;

	while (app.isOpen()) {
		

		
	}

    return 0;
}
