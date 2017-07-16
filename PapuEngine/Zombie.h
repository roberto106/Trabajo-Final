#pragma once
#include "Agent.h"
class Zombie :public Agent
{
public:
	Zombie();
	~Zombie();

	void init(float speed, glm::vec2 position);
	void draw(SpriteBacth& spritebatch);

	void update(const std::vector<std::string>& levelData,
		std::vector<Human*>& humans,
		std::vector<Zombie*>& zombies,
		std::vector<Zombie2*>& zombies2);
	Human* getNearestHuman(std::vector<Human*>& humans);
	int getPosition_X();
	int getPosition_Y();
	void zombimuerto(int x);
};

