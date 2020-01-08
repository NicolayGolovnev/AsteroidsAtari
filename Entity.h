#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "Animation.h"

const int W = 1200;
const int H = 800;

float DEGTORAD = 0.017453f;

class Entity
{
protected:
	float x, y, dx, dy, R, angle;
	bool life;
	std::string name;
	Animation anim;
public:
	Entity();
	float getX();
	float getY();
	float getR();
	void settings(Animation& a, int X, int Y, float Angle = 0, int radius = 1);
	virtual void update();
	void draw(RenderWindow& app);
	virtual ~Entity();
};

