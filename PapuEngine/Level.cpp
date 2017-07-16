#include "Level.h"
#include <fstream>
#include "ResourceManager.h"
#include "Error.h"
#include <random>
#include <iostream>
#include "GamePlayScreen.h"
Level::Level(const std::string& fileName)
{
	std::ifstream file;
	file.open(fileName);
	if (file.fail()) {
		fatalError("failed to opem " + fileName);
	}
	std::string tmp;

	file >> tmp >> _numHumans;

	std::getline(file, tmp);
	while (std::getline(file, tmp)) {
		_levelData.push_back(tmp);
	}
	parseLevel();

}

void Level::draw() {
	_spriteBatch.renderBatch();
}

void Level::setpos(int p) {
	p = pos;
}
void Level::parseLevel() {
	_spriteBatch.init();
	_spriteBatch.begin();
	ColorRGBA colorf;
	colorf.r = 255;
	colorf.g = 255;
	colorf.b = 255;
	colorf.a = 255;
	_spriteBatch.draw(glm::vec4(-100, -200, 1000,8000), glm::vec4(0, 0, 1, 1), ResourceManager::getTexture("assets/game.png").id, 0.0f, colorf);
	std::uniform_real_distribution<float>xPos2(50.0f, 750.0f);
	std::uniform_real_distribution<float>yPos2(1500.0f, 5000.0f);
	std::mt19937 randomGenerator;
	
	for (int i = 0; i < 70; i++)
	{
		

		
		_zombiesPosition.emplace_back(xPos2(randomGenerator),yPos2(randomGenerator));



	}std::uniform_real_distribution<float>xPos3(50.0f, 750.0f);
	std::uniform_real_distribution<float>yPos3(4000.0f, 6000.0f);
	std::mt19937 randomGenerator3;
	std::cout << pos<<std::endl;
	if(pos==1000)
	for (int i = 0; i < 70; i++)
	{



		_zombiesPosition.emplace_back(xPos3(randomGenerator3), yPos3(randomGenerator3));



	}

	std::mt19937 randomGenerator2;
	std::uniform_real_distribution<float>xPos(50.0f, 750.0f);
	std::uniform_real_distribution<float>yPos(2000.0f, 6000.0f);

	for (int i = 0; i < 70; i++)
	{
		_zombies2Position.emplace_back(xPos(randomGenerator2), yPos(randomGenerator2));


	}
	for (int i = 0; i < 70; i++)
	{
		_zombies2Position.emplace_back(xPos(randomGenerator2), yPos(randomGenerator2));


	}
	glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	ColorRGBA ColorRGBA;
	ColorRGBA.set(255, 255, 255, 255);
	for (int y = 0; y < _levelData.size(); y++)
	{
		for (int x = 0; x < _levelData[y].size(); x++)
		{
			char tile = _levelData[y][x];
			glm::vec4 destRect(x*TILE_WIDTH, y*TILE_WIDTH,
							   TILE_WIDTH, TILE_WIDTH);
			switch (tile)
			{
			case 'R':
			case 'B':
				_spriteBatch.draw(destRect, uvRect, 
					ResourceManager::getTexture("Textures/red_bricks.png").id
					,0.0f,ColorRGBA);
				break;
			case 'G':
				_spriteBatch.draw(destRect, uvRect,
					ResourceManager::getTexture("Textures/glass.png").id
					, 0.0f, ColorRGBA);
				break;
			case 'L':_spriteBatch.draw(destRect, uvRect,
				ResourceManager::getTexture("Textures/light_bricks.png").id
				, 0.0f, ColorRGBA);				
				break;
			case '@':
				_levelData[y][x] = '.';
				_playerPosition.x = x*TILE_WIDTH;
				_playerPosition.y = y*TILE_WIDTH;
				
				break;
	
			case '.':
				break;
			default:
				break;
			}
		}
	}
	_spriteBatch.end();
}


Level::~Level()
{
}
