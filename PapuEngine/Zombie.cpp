#include "Zombie.h"
#include "Human.h"
#include "ResourceManager.h"
#include <random>

Zombie::Zombie()
{
}
void Zombie::draw(SpriteBacth& spritebatch) {
	static int textureID = ResourceManager::getTexture("assets/spaceShips_001.png").id;
	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	

	glm::vec4 destRect(_position.x, _position.y, AGENT_WIDTH, AGENT_WIDTH);
	spritebatch.draw(destRect, uvRect, textureID, 0.0f, ColorRGBA);
}

void Zombie::init(float speed, glm::vec2 position) {
	_speed = speed;
	_position = position;
	ColorRGBA.set(255, 255, 255, 255);
}

void Zombie::update(const std::vector<std::string>& levelData,
	std::vector<Human*>& humans,
	std::vector<Zombie*>& zombies,
	std::vector<Zombie2*>& zombies2) {
	collideWithLevel(levelData);

	_position += glm::vec2(0,-5)*_speed;

	/*Human* closeHuman = getNearestHuman(humans);
	if (closeHuman != nullptr) {
		glm::vec2 direction = glm::normalize(
				closeHuman->getPosition() - _position);
		_position += direction*_speed;*/
}
int Zombie::getPosition_X()
{
	return _position.x;
}
int Zombie::getPosition_Y()
{
	return _position.y;
}
void Zombie::zombimuerto(int muerto)
{
	
}
Human* Zombie::getNearestHuman(std::vector<Human*>& humans) {
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


Zombie::~Zombie()
{
	
}
