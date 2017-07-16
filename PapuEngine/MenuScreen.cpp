#include "MenuScreen.h"
#include "ScreenIndices.h"
#include "ResourceManager.h"

#include <random>
#include <ctime>
MenuScreen::MenuScreen(Window* window) :
	_window(window)
{
	_screenIndex = SCREEN_INDEX_MENU;
}

void MenuScreen::initGUI() {
	_gui.init("GUI");
	_gui.loadScheme("TaharezLook.scheme");
	_gui.loadScheme("AlfiskoSkin.scheme");

	CEGUI::ImageManager::getSingleton().addFromImageFile("img_fondo", "menu.png");
	CEGUI::Window *background = static_cast<CEGUI::PushButton*>(_gui.createWidget("TaharezLook/StaticImage", glm::uvec4(0, 0, 1, 1), glm::vec4(0.0f), "Background"));
	background->setProperty("Image", "img_fondo");
	background->setDisabled(true);
	_gui.setFont("DejaVuSans-10");
	
	CEGUI::PushButton* gameButton =
		static_cast<CEGUI::PushButton*>(
			_gui.createWidget("AlfiskoSkin/Button",
				glm::vec4(0.45f, 0.45f, 0.1f, 0.05f), glm::vec4(0.0f),
				"Game Button"));
	gameButton->setText("Game");
	gameButton->subscribeEvent(CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(&MenuScreen::onGameClicked, this));
	

	CEGUI::PushButton* exitButton =
		static_cast<CEGUI::PushButton*>(
			_gui.createWidget("AlfiskoSkin/Button",
				glm::vec4(0.45f, 0.65f, 0.1f, 0.05f), glm::vec4(0.0f),
				"Exit Button"));
	exitButton->setText("Exit");
	exitButton->subscribeEvent(CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(&MenuScreen::onExitClicked, this));

	
	CEGUI::PushButton* Title =
		static_cast<CEGUI::PushButton*>(
			_gui.createWidget("AlfiskoSkin/Label",
				glm::vec4(0.45f, 0.15f, 0.1f, 0.05f), glm::vec4(0.0f),
				"Titulo"));
	Title->setText("Trabajo Final");
	CEGUI::PushButton* Nombre =
		static_cast<CEGUI::PushButton*>(
			_gui.createWidget("AlfiskoSkin/Label",
				glm::vec4(0.45f, 0.30f, 0.1f, 0.05f), glm::vec4(0.0f),
				"Nombre"));
	Nombre->setText("Victor Aguilar");
	CEGUI::PushButton* Nombre2 =
		static_cast<CEGUI::PushButton*>(
			_gui.createWidget("AlfiskoSkin/Label",
				glm::vec4(0.45f, 0.25f, 0.1f, 0.05f), glm::vec4(0.0f),
				"Nombre2"));
	Nombre2->setText("Roberto Nureña");


}

void MenuScreen::initSystem() {
}

MenuScreen::~MenuScreen()
{
}
bool MenuScreen::onGameClicked(const CEGUI::EventArgs& e)
{
	_currentState = ScreenState::CHANGE_NEXT;
	return true;
}
bool MenuScreen::onExitClicked(const CEGUI::EventArgs& e)
{
	_currentState = ScreenState::EXIT_APPLICATION;
	return true;
}

void MenuScreen::build() {

}
void MenuScreen::destroy() {
	_gui.destroy();
}
void MenuScreen::onExit() {

}
void MenuScreen::onEntry() {
	
	_spriteBatch.init();
	_hudSpriteBatch.init();
	initGUI();

	_spriteFont = new SpriteFont("Fonts/arial.ttf", 20);
	//_texture = ResourceManager::getTexture("assets/menu.png");
	

	
}
void MenuScreen::update() {
	checkInput();
}
void MenuScreen::drawHud() {
	char buffer[256];
	_hudSpriteBatch.begin();
	sprintf_s(buffer, "Num Humans %d", 10);
	_spriteFont->draw(_hudSpriteBatch, buffer, glm::vec2(0, 0),
		glm::vec2(0.5), 0.0f, ColorRGBA(255, 255, 255, 255));

	sprintf_s(buffer, "Num Zombies %d", 10);
	_spriteFont->draw(_hudSpriteBatch, buffer, glm::vec2(0, 36),
		glm::vec2(0.5), 0.0f, ColorRGBA(255, 255, 255, 255));
	_hudSpriteBatch.end();
	_hudSpriteBatch.renderBatch();
}
void MenuScreen::draw() {
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	_spriteBatch.renderBatch();

	drawHud();
	_gui.draw();


}
int MenuScreen::getNextScreen()const {
	return SCREEN_INDEX_GAMEPLAY;
}
int MenuScreen::getPreviousScreen() const{
	return SCREEN_INDEX_NO_SCREEN;
}
void MenuScreen::checkInput() {
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt)) {
		_gui.onSDLEvent(evnt);
	}
}


