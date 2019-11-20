#include <SFML/Graphics.hpp>
using namespace sf;

const int W = 1920;
const int H = 1080;
int main()
{
    srand(time(0));

    RenderWindow app(VideoMode(W, H), "Asteroids!");
    app.setFramerateLimit(60);

	Event newEvent;

	while (app.isOpen()) {

	}

    return 0;
}
