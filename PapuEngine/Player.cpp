#include "Player.h"
#include <SDL\SDL.h>
#include <iostream>
#include "GLTexture.h"
#include "ResourceManager.h"
void Player::draw(SpriteBacth& spritebatch) {
	static int textureID = ResourceManager::getTexture("assets/Player.png").id;
	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);


	glm::vec4 destRect(_position.x, _position.y, AGENT_WIDTH, AGENT_WIDTH);
	spritebatch.draw(destRect, uvRect, textureID, 0.0f, ColorRGBA);
}

void Player::init(float speed, glm::vec2 position, InputManager* inputManager, Camera2D* camera) {
	_speed = 5;
	_position = position;
	_camera = camera;
	_inputManager = inputManager;
	ColorRGBA.set(255, 255, 255, 255);

	
}
int Player::getPosition_X()
{
	return _position.x;
}
int Player::getPosition_Y()
{
	return _position.y;
}
void Player::update(const std::vector<std::string>& levelData,
	std::vector<Human*>& humans,
	std::vector<Zombie*>& zombies,std::vector<Zombie2*>& zombies2
	) {
	if (_inputManager->isKeyDown(SDLK_w)) {
		_position.y += _speed;
	}
	if (_inputManager->isKeyDown(SDLK_s)) {
		_position.y -= _speed;
	}
	if (_inputManager->isKeyDown(SDLK_a)) {
		_position.x -= _speed;
	}
	if (_inputManager->isKeyDown(SDLK_d)) {
		_position.x += _speed;
	}
	collideWithLevel(levelData);
}


Player::Player():_currentGun(-1)
{
}


Player::~Player()
{
}
