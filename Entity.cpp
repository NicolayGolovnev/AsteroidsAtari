#include "Entity.h"

Entity::Entity(){
	life = 1;
}

float Entity::getX() {
	return this->x;
}

float Entity::getY() {
	return this->y;
}

float Entity::getR() {
	return this->R;
}

void Entity::settings(Animation& a, int X, int Y, float Angle = 0, int radius = 1){
	anim = a;
	x = X; y = Y;
	angle = Angle;
	R = radius;
}

void Entity::update() {};

void Entity::draw(RenderWindow& app){
	anim.sprite.setPosition(x, y);
	anim.sprite.setRotation(angle + 90);
	app.draw(anim.sprite);

	CircleShape circle(R);
	circle.setFillColor(Color(255, 0, 0, 170));
	circle.setPosition(x, y);
	circle.setOrigin(R, R);
	//app.draw(circle);
}

Entity::~Entity() {};
