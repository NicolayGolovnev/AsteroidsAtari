#pragma once
#include <SFML/Graphics.hpp>
#include <list>
using namespace sf;
class Animation
{
private:
	float Frame, speed;
	Sprite sprite;
	std::vector<IntRect> frames;
public:
	Animation();
	Animation(Texture& t, int x, int y, int w, int h, int count, float speed);
	void update();
	bool isEnd();
};

