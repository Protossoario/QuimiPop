#pragma once

#include <memory>
#include <string>

#include "Window.h"
#include "InputManager.h"

class ScreenList;
class IGameScreen;

class IMainGame {
public:
	IMainGame();
	virtual ~IMainGame();

	void run();
	void exitGame();

	virtual void onInit() = 0;
	virtual void addScreens() = 0;
	virtual void onExit() = 0;

	const float getFPS() const { return m_fps; }

	int getWindowWidth() { return m_windowWidth; }
	int getWindowHeight() { return m_windowHeight; }

protected:
	virtual void update();
	virtual void draw();

	void onSDLEvent(SDL_Event& evnt);
	void getInput();

	bool init();
	bool initSystems();

	std::unique_ptr<ScreenList> m_screenList = nullptr;
	IGameScreen* m_currentScreen = nullptr;
	bool m_isRunning = false;
	float m_fps = 0.0f;

	Window m_window;
	InputManager m_inputManager;

	std::string m_windowTitle = "Default";
	int m_windowWidth = 960;
	int m_windowHeight = 540;
};