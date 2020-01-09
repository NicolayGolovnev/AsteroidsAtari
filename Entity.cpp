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

float Entity::getAngle() {
	return this->angle;
}
void Entity::setAngle(float a) {
	this->angle = a;
}

float Entity::getDx() {
	return this->dx;
}

void Entity::setDx(float a) {
	this->dx = a;
}

float Entity::getDy() {
	return this->dy;
}

void Entity::setDy(float b) {
	this->dy = b;
}

bool Entity::getLife() {
	return this->life;
}

void Entity::setLife(bool l) {
	this->life = l;
}

std::string Entity::getName() {
	return this->name;
}

void Entity::setName(std::string n) {
	this->name = n;
}

void Entity::setAnim(Animation a) {
	this->anim = a;
}

bool Entity::animIsEnd() {
	return this->anim.isEnd();
}

void Entity::settings(Animation& a, int X, int Y, float Angle = 0, int radius = 1){
	anim = a;
	x = X; y = Y;
	angle = Angle;
	R = radius;
}

void Entity::update() {
	this->anim.update();
};

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
