#pragma once
#include <string>
#include <vector>
#include "SpriteBacth.h"

using namespace std;

const int TILE_WIDTH = 64;
class Level
{

private:
	vector<string> _levelData;
	int _numHumans;
	void parseLevel();
	int pos;
	
	
public:

	void setpos(int p);
	int getNumHumans() const {
		return _numHumans;
	}
	glm::vec2 _playerPosition;
	std::vector<glm::vec2> _zombiesPosition;
	std::vector<glm::vec2> _zombies2Position;


	glm::vec2 getPlayerPosition() const { 
		return _playerPosition; 
	};

	const std::vector<std::string>& getLevelData() {
		return _levelData;
	}
	int getWidth() const {
		return _levelData[0].size();
	}
	int getHeight() const {
		return _levelData[0].size();
	}
	std::vector<glm::vec2> getZombiesPosition()const {
		return _zombiesPosition;
	};
	std::vector<glm::vec2> getZombies2Position()const {
		return _zombies2Position;
	};

	Level(const std::string& fileName);
	void draw();
	SpriteBacth _spriteBatch;
	~Level();
};

