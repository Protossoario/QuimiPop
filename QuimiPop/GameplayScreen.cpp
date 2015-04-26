#include "GameplayScreen.h"
#include "ScreenList.h"
#include "MainApp.h"

#include "glm/glm.hpp"
#include "glm/gtx/rotate_vector.hpp"
#include "glm/gtc/matrix_transform.hpp"

#define BOARD_X -425.0f
#define BOARD_Y -250.0f

GameplayScreen::GameplayScreen() : m_gameBoard(glm::vec2(BOARD_X, BOARD_Y)) {
}

GameplayScreen::~GameplayScreen() {
}

int GameplayScreen::getNextScreenIndex() const {
	return SCREEN_INDEX_NO_SCREEN;
}

int GameplayScreen::getPreviousScreenIndex() const {
	return SCREEN_INDEX_NO_SCREEN;
}

void GameplayScreen::build() {
	printf("Build!\n");
	m_app = (MainApp*)m_game;
	m_spriteBatch.init();
	m_camera.init(m_game->getWindowWidth(), m_game->getWindowHeight());
	m_gameBoard.init();
	m_gameBoard.setMoleculeSound(m_app->m_audioEngine.loadSoundEffect("Sounds/Item1B.wav"));
}

void GameplayScreen::destroy() {
	printf("Destroy!\n");
}

void GameplayScreen::onEntry() {
	printf("OnEntry!\n");
}

void GameplayScreen::onExit() {
	printf("OnExit!\n");
}

void GameplayScreen::update() {
	m_camera.update();
	m_gameBoard.update();
	if (m_app->m_inputManager.isKeyDown(SDL_BUTTON_LEFT)) {
		glm::vec2 mouseCoords = m_app->m_inputManager.getMouseCoords();
		mouseCoords = m_camera.convertScreenToWorld(mouseCoords);

		if (m_gameBoard.isPointInsideBoard(mouseCoords)) {
			m_gameBoard.setClickingDown(true);
			m_gameBoard.updateMouseCoords(mouseCoords);
		}

		//addGlow(mouseCoords, 10);
	}
	else {
		glm::vec2 mouseCoords = m_app->m_inputManager.getMouseCoords();
		mouseCoords = m_camera.convertScreenToWorld(mouseCoords);

		if (m_gameBoard.isPointInsideBoard(mouseCoords)) {
			m_gameBoard.setClickingDown(false);
			m_gameBoard.updateMouseCoords(mouseCoords);
		}
	}
	if (m_app->m_inputManager.isKeyDown(SDL_BUTTON_RIGHT)) {
		m_gameBoard.resetHoverMolecule();
	}
}

void GameplayScreen::draw() {
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glClearColor(1.0, 1.0, 1.0, 1.0);

	//glDisable(GL_DEPTH_TEST);
	// Drawing 2D sprites
	m_app->m_spriteShader.use();

	glActiveTexture(GL_TEXTURE0);
	GLint textureLocation = m_app->m_spriteShader.getUniformLocation("mySampler");
	glUniform1i(textureLocation, 0);

	GLint pLocation = m_app->m_spriteShader.getUniformLocation("P");
	glm::mat4 cameraMatrix = m_camera.getCameraMatrix();
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	m_spriteBatch.begin();

	glm::vec4 backgroundRect(-m_game->getWindowWidth() / 2.0f, -m_game->getWindowHeight() / 2.0f, m_game->getWindowWidth(), m_game->getWindowHeight());
	glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	static GLTexture backgroundTexture = ResourceManager::getTexture("Textures/Background.png");
	ColorRGBA8 color(255, 255, 255, 255);
	m_spriteBatch.draw(backgroundRect, uvRect, backgroundTexture.textureId, 0.0f, color);

	m_gameBoard.draw(m_spriteBatch);

	m_spriteBatch.end();

	m_spriteBatch.renderBatch();

	m_app->m_particleEngine.draw(&m_spriteBatch);

	glBindTexture(GL_TEXTURE_2D, 0);

	m_app->m_spriteShader.unuse();

	/*drawHUD();

	glEnable(GL_DEPTH_TEST);

	// Drawing 3D molecule mesh
	m_app->m_meshShader.use();

	static float moleculeScale = 35.0f;

	static glm::mat4 projection = glm::ortho(0.0f, (float)m_game->getWindowWidth(), 0.0f, (float)m_game->getWindowHeight(), -1000.0f, 1000.0f);
	GLint projectionLocation = m_app->m_meshShader.getUniformLocation("projection");
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &(projection[0][0]));

	glm::mat4 transform;
	transform = glm::translate(transform, glm::vec3(815.0f, m_sidebarOffsetY + 225.0f, 100.0f));
	transform = glm::scale(transform, glm::vec3(moleculeScale));
	transform = glm::rotate(transform, 45.0f, glm::vec3(0.0f, 0.0f, 1.0f));
	transform = glm::rotate(transform, m_angle, glm::vec3(1.0f, 1.0f, 0.0f));
	GLint transformLocation = m_meshShader.getUniformLocation("transform");
	glUniformMatrix4fv(transformLocation, 1, GL_FALSE, &(transform[0][0]));

	std::map<Molecule, Mesh>::iterator iter = m_molecules.find(m_gameBoard.getHoverMolecule());
	if (iter != m_molecules.end()) {
		iter->second.render(m_meshShader);
	}

	m_meshShader.unuse();*/
}