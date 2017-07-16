#include "GameOverScreen.h"
#include "ScreenIndices.h"
#include "ResourceManager.h"

#include <random>
#include <ctime>


GameOverScreen::GameOverScreen(Window* window) :
	_window(window)
{
	_screenIndex = SCREEN_INDEX_GAMEOVER;
}


GameOverScreen::~GameOverScreen()
{
}
void GameOverScreen::initGUI() {
	_gui.init("GUI");
	_gui.loadScheme("TaharezLook.scheme");
	_gui.loadScheme("AlfiskoSkin.scheme");

	CEGUI::ImageManager::getSingleton().addFromImageFile("img_fondo2", "menu.png");
	CEGUI::Window *background = static_cast<CEGUI::PushButton*>(_gui.createWidget("TaharezLook/StaticImage", glm::uvec4(0, 0, 1, 1), glm::vec4(0.0f), "Background"));
	background->setProperty("Image", "img_fondo");
	background->setDisabled(true);
	_gui.setFont("Jura-18");



	CEGUI::PushButton* exitButton =
		static_cast<CEGUI::PushButton*>(
			_gui.createWidget("AlfiskoSkin/Button",
				glm::vec4(0.38f, 0.65f, 0.2f, 0.1f), glm::vec4(0.0f),
				"Exit Button"));
	exitButton->setText("Exit");
	exitButton->subscribeEvent(CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(&GameOverScreen::onExitClicked, this));
	char buffer[25];
	sprintf_s(buffer, "Puntaje %d", puntaje);

	CEGUI::PushButton* Title =
		static_cast<CEGUI::PushButton*>(
			_gui.createWidget("AlfiskoSkin/Label",
				glm::vec4(0.28f, 0.15f, 0.4f, 0.4f), glm::vec4(0.0f),
				"Titulo"));
	Title->setText("GAME OVER ");
	CEGUI::PushButton* puntos =
		static_cast<CEGUI::PushButton*>(
			_gui.createWidget("AlfiskoSkin/Label",
				glm::vec4(0.28f, 0.10f, 0.4f, 0.4f), glm::vec4(0.0f),
				"Puntos"));
	puntos->setText(buffer);
	/*CEGUI::PushButton* Nombre =
	static_cast<CEGUI::PushButton*>(
	_gui.createWidget("AlfiskoSkin/Label",
	glm::vec4(0.45f, 0.30f, 0.1f, 0.05f), glm::vec4(0.0f),
	"Nombre"));
	Nombre->setText("Roberto Nureña");*/



}

void GameOverScreen::initSystem() {
}


bool GameOverScreen::onGameClicked(const CEGUI::EventArgs& e)
{
	_currentState = ScreenState::CHANGE_NEXT;
	return true;
}
bool GameOverScreen::onExitClicked(const CEGUI::EventArgs& e)
{
	_currentState = ScreenState::EXIT_APPLICATION;
	return true;
}

void GameOverScreen::build() {

}
void GameOverScreen::destroy() {
	_gui.destroy();
}
void GameOverScreen::onExit() {

}
void GameOverScreen::onEntry() {

	_spriteBatch.init();
	_hudSpriteBatch.init();
	initGUI();

	_spriteFont = new SpriteFont("Fonts/arial.ttf", 20);
	//_texture = ResourceManager::getTexture("assets/menu.png");



}
void GameOverScreen::update() {
	checkInput();
}
void GameOverScreen::drawHud() {
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
void GameOverScreen::draw() {
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	_spriteBatch.renderBatch();

	drawHud();
	_gui.draw();


}
int GameOverScreen::getNextScreen()const {
	return SCREEN_INDEX_NO_SCREEN;
}
int GameOverScreen::getPreviousScreen() const {
	return SCREEN_INDEX_GAMEPLAY;
}
void GameOverScreen::checkInput() {
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt)) {
		_gui.onSDLEvent(evnt);
	}
}


