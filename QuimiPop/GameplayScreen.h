#pragma once

#include "IGameScreen.h"
#include "Camera2D.h"
#include "GameBoard.h"
#include "SpriteBatch.h"

class MainApp;

class GameplayScreen : public IGameScreen {
public:
	GameplayScreen();
	~GameplayScreen();

	virtual int getNextScreenIndex() const override;
	virtual int getPreviousScreenIndex() const override;
	virtual void build() override;
	virtual void destroy() override;
	virtual void onEntry() override;
	virtual void onExit() override;
	virtual void update() override;
	virtual void draw() override;

private:
	MainApp* m_app = nullptr;

	Camera2D m_camera;

	GameBoard m_gameBoard;

	SpriteBatch m_spriteBatch;
};