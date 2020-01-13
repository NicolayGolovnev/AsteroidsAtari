#include "Animation.h"

Animation::Animation() {}
Animation::Animation(Texture& t, int x, int y, int w, int h, int countOne, int countTwo, float speed)
{
	this->Frame = 0;
	this->Speed = speed;

	for (int j = 0; j < countTwo; j++)
		for (int i = 0; i < countOne; i++)
			frames.push_back(IntRect(x + i * w, y + j * h, w, h));

	sprite.setTexture(t);
	sprite.setOrigin(w / 2, h / 2);
	sprite.setTextureRect(frames[0]);
}


void Animation::update()
{
	this->Frame += this->Speed;
	int n = frames.size();
	if (this->Frame >= n) this->Frame -= n;
	if (n > 0) sprite.setTextureRect(frames[int(this->Frame)]);
}

bool Animation::isEnd()
{
	return this->Frame + this->Speed >= frames.size();
}