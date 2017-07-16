#include "GamePlayScreen.h"
#include "Game.h"
#include "ScreenIndices.h"
#include <random>
#include <ctime>
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <Windows.h>

int bala = 0;
int vidas = 5;
//int puntaje = 0;
double pos =200;
double timer = 0;


bool GamePlayScreen::onExitClicked()
{
	_currentState = ScreenState::EXIT_APPLICATION;
	return true;
}

GamePlayScreen::GamePlayScreen(Window* window):
	_window(window)
{
	_screenIndex = SCREEN_INDEX_GAMEPLAY;
}


GamePlayScreen::~GamePlayScreen()
{
}


void GamePlayScreen::build() {

}
void GamePlayScreen::destroy() {

}
void GamePlayScreen::onExit() {
}

void GamePlayScreen::onEntry() {
	initWorld();
	initSystem();
	_currentLevel = 0;
	_levels.push_back(new Level("Levels/level1.txt"));
	_spriteBatch.init();
	_hudSpriteBatch.init();
	initGUI();
	_spriteFont = new SpriteFont("Fonts/arial.ttf", 64);
	_camera2d.init(_window->getScreenWidth(),
		_window->getScreenHeight());

	_hudCamera.init(_window->getScreenWidth(),
		_window->getScreenHeight());

	_hudCamera.setPosition(glm::vec2(_window->getScreenWidth() /2, _window->getScreenHeight() / 2));

	_player = new Player();
	_player->init(1.0f, _levels[_currentLevel]->getPlayerPosition(), &_game->_inputManager, &_camera2d);
	_humans.push_back(_player);

	const std::vector<glm::vec2>& zombiePosition =
		_levels[_currentLevel]->getZombiesPosition();

	const std::vector<glm::vec2>& zombie2Position =
		_levels[_currentLevel]->getZombies2Position();


	for (size_t i = 0; i < zombiePosition.size(); i++)
	{
		_zombies.push_back(new Zombie());
		_zombies.back()->init(1.3f, zombiePosition[i]);
	}

	for (size_t i = 0; i < zombie2Position.size(); i++)
	{
		_zombies2.push_back(new Zombie2());
		_zombies2.back()->init(1.3f, zombie2Position[i]);
	}

	std::mt19937 randomEngine(time(nullptr));
	std::uniform_int_distribution<int>randPosX(
		1, _levels[_currentLevel]->getWidth() - 2);
	std::uniform_int_distribution<int>randPosY(
		1, _levels[_currentLevel]->getHeight() - 2);

	for (int i = 0; i < _levels[_currentLevel]->getNumHumans(); i++)
	{
		_humans.push_back(new Human());
		glm::vec2 pos(randPosX(randomEngine)*TILE_WIDTH,
			randPosY(randomEngine)*TILE_WIDTH);
		_humans.back()->init(1.0f, pos);
	}
}

void GamePlayScreen::drawHud() {
	char buffer[256];

	glm::mat4 projectionMatrix = _hudCamera.getCameraMatrix();
	GLint pUniform = _program.getUniformLocation("P");
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);
	_hudSpriteBatch.begin();
	sprintf_s(buffer, "Vidas %d", vidas);
	_spriteFont->draw(_hudSpriteBatch, buffer, glm::vec2(0, 450),
		glm::vec2(0.5), 0.0f, ColorRGBA(255, 255, 255, 255));

	sprintf_s(buffer, "Puntaje %d", puntaje);
	_spriteFont->draw(_hudSpriteBatch, buffer, glm::vec2(400, 450),
		glm::vec2(0.5), 0.0f, ColorRGBA(255, 255, 255, 255));
	_hudSpriteBatch.end();
	_hudSpriteBatch.renderBatch();
}

void GamePlayScreen::initWorld() {
	b2Vec2 gravity(0.0f, -0.8f);
	_world = std::make_unique<b2World>(gravity);
	b2BodyDef grounDef;
	grounDef.position.Set(0.0f, -30.0f);
	b2Body* groundBody = _world->CreateBody(&grounDef);
	b2PolygonShape groundBox;
	groundBox.SetAsBox(10.0f, 10.0f);
	groundBody->CreateFixture(&groundBox, 0.0f);
}

void GamePlayScreen::initGUI()
{
	_gui.init("GUI");
	_gui.loadScheme("TaharezLook.scheme");
	_gui.loadScheme("AlfiskoSkin.scheme");
}

void GamePlayScreen::draw() {
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_program.use();
	

	for (size_t i = 0;i<_zombies.size();i++)
	{
		for (size_t j = 0;j<_bullets.size();j++)
		{
			if(i<_zombies.size())
			if (_zombies[i]->getPosition_X() <= _bullets[j].getPosition_X() + 30 && _zombies[i]->getPosition_X() >= _bullets[j].getPosition_X() - 30)
			{
				
				if (_zombies[i]->getPosition_Y() <= _bullets[j].getPosition_Y() + 30 && _zombies[i]->getPosition_Y() >= _bullets[j].getPosition_Y() - 30)
				{
					puntaje += 10;
					//
					cout << "\a";
					_bullets.erase(_bullets.begin()+j);
					_zombies.erase(_zombies.begin() + i);
					
				}

			}
			
		}
	}
	for (size_t i = 0;i<_zombies2.size();i++)
	{
		for (size_t j = 0;j<_bullets.size();j++)
		{
			if (i<_zombies2.size())
				if (_zombies2[i]->getPosition_X() <= _bullets[j].getPosition_X() + 30 && _zombies2[i]->getPosition_X() >= _bullets[j].getPosition_X() - 30)
				{

					if (_zombies2[i]->getPosition_Y() <= _bullets[j].getPosition_Y() + 30 && _zombies2[i]->getPosition_Y() >= _bullets[j].getPosition_Y() - 30)
					{
						puntaje += 20;
						//
						cout << "\a";
						_bullets.erase(_bullets.begin() + j);
						_zombies2.erase(_zombies2.begin() + i);
					
					}

				}	

		}
	}
	
	for (size_t i = 0;i<_zombies2.size();i++)
	{
		for (int j = 0;j<1;j++)
		{
			if (i<_zombies2.size())
				if (_zombies2[i]->getPosition_X() <= _player->getPosition_X() + 30 && _zombies2[i]->getPosition_X() >= _player->getPosition_X() - 30)
				{

					if (_zombies2[i]->getPosition_Y() <= _player->getPosition_Y() + 30 && _zombies2[i]->getPosition_Y() >= _player->getPosition_Y() - 30)
					{
						Beep(523, 500);
						vidas -= 2;
						//
						_zombies2.erase(_zombies2.begin() + i);
					
					}

				}

		}
	}

	for (size_t i = 0;i<_zombies.size();i++)
	{
		for (int j = 0;j<1;j++)
		{
			if (i<_zombies.size())
				if (_zombies[i]->getPosition_X() <= _player->getPosition_X() + 30 && _zombies[i]->getPosition_X() >= _player->getPosition_X() - 30)
				{

					if (_zombies[i]->getPosition_Y() <= _player->getPosition_Y() + 30 && _zombies[i]->getPosition_Y() >= _player->getPosition_Y() - 30)
					{
						Beep(523, 500);

						vidas -= 1;
						//
						_zombies.erase(_zombies.begin() + i);
					
					}

				}

		}
	}

	
	
	
	_spriteBatch.begin();


	_levels[_currentLevel]->draw();

	for (size_t i = 0; i < _zombies.size(); i++)
	{
		_zombies[i]->draw(_spriteBatch);
	}


	for (size_t i = 0; i < _zombies2.size(); i++)
	{
		_zombies2[i]->draw(_spriteBatch);
	}

	//std::cout << bala << std::endl;
	timer += 0.5;
//	std::cout << timer << std::endl;
	if (bala == 0 )
		for (int i = 0; i < _bullets.size(); i++)
		{
			_bullets[i].draw(_spriteBatch);
		}

	if (bala == 1)
		for (int i = 0; i < _bullets1.size(); i++)
		{
			_bullets1[i].draw1(_spriteBatch);
		}
	else if (bala == 2)
		for (int i = 0; i < _bullets2.size(); i++)
		{
			_bullets2[i].draw2(_spriteBatch);
		}
	else if (bala == 3)
		for (int i = 0; i < _bullets3.size(); i++)
		{
			_bullets3[i].draw3(_spriteBatch);
		}

	_player->draw(_spriteBatch);
	_spriteBatch.end();
	_spriteBatch.renderBatch();
	glActiveTexture(GL_TEXTURE0);
	GLuint pLocation =
		_program.getUniformLocation("P");
	glm::mat4 cameraMatrix = _camera2d.getCameraMatrix();
	drawHud();

	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	GLuint imageLocation = _program.getUniformLocation("myImage");
	glUniform1i(imageLocation, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	_program.unuse();
	cout << pos << endl;
	if (vidas <= 0|| pos>5000)
	{
		_currentState = ScreenState::CHANGE_NEXT;
	}
	//_gui.draw();
}
void GamePlayScreen::update() {
	checkInput();
	
	_camera2d.update();
	
	for (size_t i = 0; i < _humans.size(); i++)
	{

		_humans[i]->update(_levels[_currentLevel]->getLevelData(), _humans, _zombies,_zombies2);
	}
	for (int i = 0; i < _bullets.size();)
	{
		if (_bullets[i].update()) {
			_bullets[i] = _bullets.back();
			_bullets.pop_back();
		}

		else {
			i++;
		}
	}
	for (int i = 0; i < _bullets1.size();)
	{
		if (_bullets1[i].update()) {
			_bullets1[i] = _bullets1.back();
			_bullets1.pop_back();
		}

		else {
			i++;
		}
	}
	for (int i = 0; i < _bullets2.size();)
	{
		if (_bullets2[i].update() ) {
			_bullets2[i] = _bullets2.back();
			_bullets2.pop_back();
		}

		else {
			i++;
		}
	}
	for (int i = 0; i < _bullets3.size();)
	{
		if (_bullets3[i].update()) {
			_bullets3[i] = _bullets3.back();
			_bullets3.pop_back();
		}

		else {
			i++;
		}
	}
	for (size_t i = 0; i < _zombies.size(); i++)
	{
		_zombies[i]->update(_levels[_currentLevel]->getLevelData(),
			_humans, _zombies, _zombies2);
	}

	for (size_t i = 0; i < _zombies2.size(); i++)
	{
		_zombies2[i]->update(_levels[_currentLevel]->getLevelData(),
			_humans, _zombies, _zombies2);
	}
	pos = pos + 2.0;
	_camera2d.setPosition(glm::vec2(500,pos));

	_hudCamera.update();
}

void GamePlayScreen::initSystem()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	_program.compileShaders("Shaders/colorShaderVert.txt",
		"Shaders/colorShaderFrag.txt");
	_program.addAtribute("vertexPosition");
	_program.addAtribute("vertexColor");
	_program.addAtribute("vertexUV");
	_program.linkShader();
}


void GamePlayScreen::checkInput() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		_game->onSDLEvent(event);
		_gui.onSDLEvent(event);

		switch (event.type)
		{

		case SDL_MOUSEMOTION:
			_inputManager.setMouseCoords(event.motion.x, event.motion.y);
			break;
		case  SDL_KEYUP:
			_inputManager.releaseKey(event.key.keysym.sym);
			break;
		case  SDL_KEYDOWN:
			_inputManager.pressKey(event.key.keysym.sym);
			break;
		case SDL_MOUSEBUTTONDOWN:
			_inputManager.pressKey(event.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			_inputManager.releaseKey(event.button.button);

		}
		if (_inputManager.isKeyDown(SDL_BUTTON_LEFT) && timer>15) {
			bala = 0;
			timer = 0;
			glm::vec2 mouseCoords = _camera2d.convertScreenToWorl(_inputManager.getMouseCoords());

			glm::vec2 playerPosition(_player->getPosition());

			glm::vec2 direction = mouseCoords - playerPosition;
			direction = glm::normalize(direction);
			_bullets.emplace_back(playerPosition, direction, 5.0f, 150);
		}		if (_inputManager.isKeyDown(SDLK_u)) {
			bala = 1;
			glm::vec2 mouseCoords = _camera2d.convertScreenToWorl(_inputManager.getMouseCoords());

			glm::vec2 playerPosition(_player->getPosition());

			glm::vec2 direction = mouseCoords - playerPosition;
			direction = glm::normalize(direction);
			_bullets1.emplace_back(playerPosition, direction, 20.0f, 1000);
		}
		if (_inputManager.isKeyDown(SDLK_i)) {
			bala = 2;
			glm::vec2 mouseCoords = _camera2d.convertScreenToWorl(_inputManager.getMouseCoords());

			glm::vec2 playerPosition(_player->getPosition());

			glm::vec2 direction = mouseCoords - playerPosition;
			direction = glm::normalize(direction);
			_bullets2.emplace_back(playerPosition, direction, 20.0f, 1000);
		}
		if (_inputManager.isKeyDown(SDLK_o)) {
			bala = 3;
			glm::vec2 mouseCoords = _camera2d.convertScreenToWorl(_inputManager.getMouseCoords());

			glm::vec2 playerPosition(_player->getPosition());

			glm::vec2 direction = mouseCoords - playerPosition;
			direction = glm::normalize(direction);
			_bullets3.emplace_back(playerPosition, direction, 20.0f, 1000);
		}


	}
}


int GamePlayScreen::getNextScreen() const {
	return SCREEN_INDEX_GAMEOVER;
};

int GamePlayScreen::getPreviousScreen() const {
	return SCREEN_INDEX_MENU;
}
