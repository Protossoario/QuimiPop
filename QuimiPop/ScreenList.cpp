#include "ScreenList.h"
#include "IGameScreen.h"

ScreenList::ScreenList(IMainGame* game) : m_game(game) {}

ScreenList::~ScreenList() {}

IGameScreen* ScreenList::moveNext() {
	IGameScreen* currentScreen = getCurrentScreen();
	if (currentScreen->getNextScreenIndex() != SCREEN_INDEX_NO_SCREEN) {
		m_currentScreenIndex = currentScreen->getNextScreenIndex();
	}
	return getCurrentScreen();
}

IGameScreen* ScreenList::movePrevious() {
	IGameScreen* currentScreen = getCurrentScreen();
	if (currentScreen->getPreviousScreenIndex() != SCREEN_INDEX_NO_SCREEN) {
		m_currentScreenIndex = currentScreen->getPreviousScreenIndex();
	}
	return getCurrentScreen();
}

void ScreenList::setScreen(int nextScreen){
	m_currentScreenIndex = nextScreen;
}

void ScreenList::addScreen(IGameScreen* newScreen) {
	newScreen->m_screenIndex = m_screens.size();
	m_screens.push_back(newScreen);
	newScreen->setParentGame(m_game);
	newScreen->build();
}

void ScreenList::destroy() {
	for (size_t i = 0; i < m_screens.size(); i++) {
		m_screens[i]->destroy();
	}
	m_screens.resize(0);
	m_currentScreenIndex = SCREEN_INDEX_NO_SCREEN;
}

IGameScreen* ScreenList::getCurrentScreen() {
	if (m_currentScreenIndex == SCREEN_INDEX_NO_SCREEN) return nullptr;
	return m_screens[m_currentScreenIndex];
}