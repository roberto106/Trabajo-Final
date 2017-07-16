#include "Zombie2.h"
#include "Human.h"
#include "ResourceManager.h"
#include <random>


Zombie2::Zombie2()
{
}


void Zombie2::draw(SpriteBacth& spritebatch) {
	static int textureID = ResourceManager::getTexture("assets/spaceShips_003.png").id;
	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);


	glm::vec4 destRect(_position.x, _position.y, AGENT_WIDTH, AGENT_WIDTH);
	spritebatch.draw(destRect, uvRect, textureID, 0.0f, ColorRGBA);
}
int Zombie2::getPosition_X()
{
	return _position.x;
}
int Zombie2::getPosition_Y()
{
	return _position.y;
}
void Zombie2::init(float speed, glm::vec2 position) {
	_speed = speed;
	_position = position;
	ColorRGBA.set(255, 255, 255, 255);
}

void Zombie2::update(const std::vector<std::string>& levelData,
	std::vector<Human*>& humans,
	std::vector<Zombie*>& zombies,
	std::vector<Zombie2*>& zombies2) {
	collideWithLevel(levelData);

	Human* closeHuman = getNearestHuman(humans);
	if (closeHuman != nullptr) {
		glm::vec2 direction = glm::normalize(
			closeHuman->getPosition() - _position);
		_position += direction*_speed;
	}
}

Human* Zombie2::getNearestHuman(std::vector<Human*>& humans) {
	Human* closestHuman = nullptr;

	float smallestDistance = 88888888888.0f;

	for (size_t i = 0; i < humans.size(); i++)
	{
		glm::vec2 dist = humans[i]->getPosition() - _position;
		float distance = glm::length(dist);
		if (distance < smallestDistance) {
			smallestDistance = distance;
			closestHuman = humans[i];
		}
	}
	return closestHuman;

}


Zombie2::~Zombie2()
{
}