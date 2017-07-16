#include "Bala.h"
#include "ResourceManager.h"
#include "GLTexture.h"


Bala::Bala(glm::vec2 po, glm::vec2 dir, float speed, int lifeTime)
{
	_lifeTime = lifeTime;
	_position = po;
	_direction = dir;
	_speed = speed;
}
int Bala::getPosition_X()
{
	return _position.x;
}
int Bala::getPosition_Y()
{
	return _position.y;
}
void Bala::draw(SpriteBacth& spriteBatch) {
	ColorRGBA color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	static GLTexture texture = ResourceManager::getTexture("assets/spaceMissiles_001.png");
	glm::vec4 posAnSize = glm::vec4(_position.x, _position.y, 30, 30);
	spriteBatch.draw(posAnSize, uv, texture.id, 0.0f, color);
}
void Bala::draw1(SpriteBacth& spriteBatch) {
	ColorRGBA color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	static GLTexture texture = ResourceManager::getTexture("assets/spaceMissiles_003.png");
	glm::vec4 posAnSize = glm::vec4(_position.x, _position.y, 30, 30);
	spriteBatch.draw(posAnSize, uv, texture.id, 0.0f, color);
}void Bala::draw2(SpriteBacth& spriteBatch) {
	ColorRGBA color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	static GLTexture texture = ResourceManager::getTexture("assets/spaceMissiles_005.png");
	glm::vec4 posAnSize = glm::vec4(_position.x, _position.y, 30, 30);
	spriteBatch.draw(posAnSize, uv, texture.id, 0.0f, color);
}void Bala::draw3(SpriteBacth& spriteBatch) {
	ColorRGBA color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	static GLTexture texture = ResourceManager::getTexture("assets/spaceMissiles_007.png");
	glm::vec4 posAnSize = glm::vec4(_position.x, _position.y, 30, 30);
	spriteBatch.draw(posAnSize, uv, texture.id, 0.0f, color);
}
bool Bala::update() {
	_position += _direction * _speed;
	_lifeTime--;
	if (_lifeTime == 0) {
		return true;
	}
	return false;
}
Bala::~Bala()
{
}
