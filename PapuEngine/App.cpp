#include "App.h"
#include "ScreenList.h"


App::App()
{
}


void App::onInit() {

}
void App::addScreens() {
	_gamePlayScreen =std::make_unique<GamePlayScreen>(&_window);
	_gamePlayScreen->setInputManager(_inputManager);
	_menuScreen = std::make_unique<MenuScreen>(&_window);

	_gameOverScreen = std::make_unique<GameOverScreen>(&_window);


	_screenList->addScreen(_menuScreen.get());
	_screenList->addScreen(_gamePlayScreen.get());
	_screenList->addScreen(_gameOverScreen.get());
	_screenList->setScreen(
		_menuScreen->getIndex());
}

void App::onExit() {
}


App::~App()
{
}
