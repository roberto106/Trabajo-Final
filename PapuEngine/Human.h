#pragma once
#include "Agent.h"

class Human : public Agent
{

protected:
	glm::vec2 _direction;
public:
	Human();
	~Human();
	void init(float speed, glm::vec2 position);
	void draw(SpriteBacth& spritebatch);
	void update(const std::vector<std::string>& levelData,
		std::vector<Human*>& humans,
		std::vector<Zombie*>& zombies,std::vector<Zombie2*>& zombies2);

};

