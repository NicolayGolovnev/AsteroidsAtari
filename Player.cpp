#include "Player.h"

Player::Player()
	{
		name = "player";
	}

bool Player::getThrust() {
	return this->thrust;
}

void Player::setThrust(bool t) {
	this->thrust = t;
}

void Player::update()
{
	if (thrust)
	{
		dx += cos(angle * DEGtoRAD) * 0.15;
		dy += sin(angle * DEGtoRAD) * 0.15;
	}
	else
	{
		dx *= 0.97;
		dy *= 0.97;
	}

	int maxSpeed = 15;
	float speed = sqrt(dx * dx + dy * dy);
	if (speed > maxSpeed)
	{
		dx *= maxSpeed / speed;
		dy *= maxSpeed / speed;
	}

	x += dx;
	y += dy;

	if (x > W) x = 0; if (x < 0) x = W;
	if (y > H) y = 0; if (y < 0) y = H;
}
