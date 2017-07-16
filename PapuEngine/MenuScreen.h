#pragma once
#include "IGameScreen.h"
#include "Window.h"
#include "SpriteBacth.h"
#include "GLS_Program.h"
#include "GUI.h"
#include <vector>
#include "GLTexture.h"
#include "SpriteFont.h"

class MenuScreen : public IGameScreen
{
private:
	Window* _window = nullptr;
	SpriteBacth _spriteBatch;
	bool onGameClicked(const CEGUI::EventArgs& e);
	bool onExitClicked(const CEGUI::EventArgs& e);
	GLTexture _texture;

	SpriteFont* _spriteFont;
	SpriteBacth  _hudSpriteBatch;
	GUI _gui;
	void drawHud();
public:
	MenuScreen(Window* window);
	virtual void build() override;
	virtual void destroy() override;
	virtual void onExit() override;
	virtual void onEntry() override;

	virtual void initGUI()override;
	virtual void draw()override;
	virtual void update()override;
	virtual void initSystem() override;
	virtual int getNextScreen() const override;
	virtual int getPreviousScreen() const override;
	virtual void checkInput() override;
	~MenuScreen();
};

