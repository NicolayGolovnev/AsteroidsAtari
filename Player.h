#pragma once
#include "Entity.h"

class Player : public Entity
{
private:
	bool thrust;
	int score;
public:
	Player();
	bool getThrust();
	void setThrust(bool t);
	int getScore();
	void setScore(int s);
	void update();

};

