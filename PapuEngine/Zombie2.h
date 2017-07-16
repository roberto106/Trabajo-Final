#pragma once
#include "Agent.h"
class Zombie2 :public Agent
{
public:
	Zombie2();
	~Zombie2();

	void init(float speed, glm::vec2 position);
	void draw(SpriteBacth& spritebatch);

	void update(const std::vector<std::string>& levelData,
		std::vector<Human*>& humans,
		std::vector<Zombie*>& zombies,
		std::vector<Zombie2*>& zombies2);
	Human* getNearestHuman(std::vector<Human*>& humans);
	int getPosition_X();
	int getPosition_Y();
};


