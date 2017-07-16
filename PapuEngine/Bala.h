#pragma once
#include <glm/glm.hpp>
#include "SpriteBacth.h"
class Bala
{
private:
	float _speed;
	glm::vec2 _direction;
	glm::vec2 _position;
	int _lifeTime;
public:

	Bala(glm::vec2 po, glm::vec2 dir, float speed, int lifeTime);
	void draw(SpriteBacth& spriteBatch);
	void draw1(SpriteBacth& spriteBatch);
	void draw2(SpriteBacth& spriteBatch);
	void draw3(SpriteBacth& spriteBatch);
	int getPosition_X();
	int getPosition_Y();



	bool update();
	~Bala();
};

