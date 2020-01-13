#pragma once
#include <SFML/Graphics.hpp>
#include <list>
using namespace sf;
class Animation
{
public:
	float Frame, Speed;
	Sprite sprite;
	std::vector<IntRect> frames;
	Animation();
	Animation(Texture& t, int x, int y, int w, int h, int countOne, int countTwo, float speed);
	void update();
	bool isEnd();
};

