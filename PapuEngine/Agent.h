#pragma once
#include <glm\glm.hpp>
#include "SpriteBacth.h"
#include "GLTexture.h"

class Zombie;
class Human;
class Zombie2;

const float AGENT_WIDTH = 60.0f;
const float AGENT_RADIUS = AGENT_WIDTH / 2.0f;

class Agent
{
protected:
	glm::vec2 _position;
	float _speed;
	ColorRGBA ColorRGBA;
	void checkTilePosition(const std::vector<std::string>& levelData, 
		std::vector<glm::vec2>& collideTilePosition,float x, float y );
	void collideWithTile(glm::vec2 tilePos);

public:
	Agent();
	glm::vec2 getPosition()const { return _position; };
	virtual void update(const std::vector<std::string>& levelData,
						std::vector<Human*>& humans,
						std::vector<Zombie*>& zombies,std::vector<Zombie2*>& zombies2) = 0;
						
	bool collideWithLevel(const std::vector<std::string>& levelData);
	virtual ~Agent();
	bool collideWithAgent(Agent* agent);
};

