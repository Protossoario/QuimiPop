#include "IMainGame.h"
#include "Timing.h"
#include "ScreenList.h"
#include "IGameScreen.h"

IMainGame::IMainGame() {
	m_screenList = std::make_unique<ScreenList>(this);
}

IMainGame::~IMainGame() {

}

void IMainGame::run() {
	if (!init()) return;

	FPSLimiter limiter;
	limiter.setMaxFPS(60.0f);

	m_isRunning = true;
	while (m_isRunning) {
		limiter.begin();

		getInput();
		m_inputManager.update();

		update();
		draw();

		m_window.swapBuffer();
		m_fps = limiter.end();
	}
}

void IMainGame::exitGame() {
	m_currentScreen->onExit();
	if (m_screenList) {
		m_screenList->destroy();
		m_screenList.reset();
	}
	m_isRunning = false;
}

void IMainGame::update() {
	if (m_currentScreen) {
		switch (m_currentScreen->getState()) {
		case ScreenState::RUNNING:
			m_currentScreen->update();
			break;

		case ScreenState::CHANGE_NEXT:
			m_currentScreen->onExit();
			m_currentScreen = m_screenList->moveNext();
			if (m_currentScreen) {
				m_currentScreen->setRunning();
				m_currentScreen->onEntry();
			}
			break;

		case ScreenState::CHANGE_PREVIOUS:
			m_currentScreen->onExit();
			m_currentScreen = m_screenList->movePrevious();
			if (m_currentScreen) {
				m_currentScreen->setRunning();
				m_currentScreen->onEntry();
			}
			break;

		case ScreenState::EXIT_APPLICATION:
			exitGame();
			break;

		default:
			break;
		}
	}
	else {
		exitGame();
	}
}

void IMainGame::draw() {
	glViewport(0, 0, m_window.getScreenWidth(), m_window.getScreenHeight());
	if (m_currentScreen && m_currentScreen->getState() == ScreenState::RUNNING) {
		m_currentScreen->draw();
	}
}

void IMainGame::onSDLEvent(SDL_Event& evnt) {
	switch (evnt.type) {
	case SDL_QUIT:
		m_isRunning = false;
		break;

	case SDL_MOUSEMOTION:
		m_inputManager.setMouseCoords((float)evnt.motion.x, (float)evnt.motion.y);
		break;

	case SDL_KEYDOWN:
		m_inputManager.pressKey(evnt.key.keysym.sym);
		break;

	case SDL_KEYUP:
		m_inputManager.releaseKey(evnt.key.keysym.sym);
		break;

	case SDL_MOUSEBUTTONDOWN:
		m_inputManager.pressKey(evnt.button.button);
		break;

	case SDL_MOUSEBUTTONUP:
		m_inputManager.releaseKey(evnt.button.button);
		break;
	}
}

void IMainGame::getInput() {
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt)) {
		onSDLEvent(evnt);
	}
}

bool IMainGame::init() {
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	initSystems();

	printf("OpenGL version %s\n", glGetString(GL_VERSION));
	printf("GLSL version %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

	onInit();
	addScreens();

	m_currentScreen = m_screenList->getCurrentScreen();
	m_currentScreen->onEntry();
	m_currentScreen->setRunning();

	return true;
}

bool IMainGame::initSystems() {
	m_window.create(m_windowTitle, m_windowWidth, m_windowHeight, 0);
	return true;
}