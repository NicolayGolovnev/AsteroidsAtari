#pragma once
#include "Entity.h"

class Player : public Entity
{
private:
	bool thrust;
public:
	Player();
	bool getThrust();
	void setThrust(bool t);
	void update();

};

