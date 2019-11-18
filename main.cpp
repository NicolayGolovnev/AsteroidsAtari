#include <SFML/Graphics.hpp>
using namespace sf;

const int W = 1200;
const int H = 800;
int main()
{
    srand(time(0));

    RenderWindow app(VideoMode(W, H), "Asteroids!");
    app.setFramerateLimit(60);

    return 0;
}
