#include "MainApp.h"
#include "ScreenList.h"
#include "ResourceManager.h"

#define WIN_WIDTH 960
#define WIN_HEIGHT 540

MainApp::MainApp() {
	m_windowTitle = "QuimiPop";
	m_windowWidth = WIN_WIDTH;
	m_windowHeight = WIN_HEIGHT;
}

MainApp::~MainApp() {
}

void MainApp::onInit() {
	m_hudFont = std::make_unique<SpriteFont>("Fonts/chemistry.ttf", 32);

	m_glowingParticles = std::make_unique<ParticleBatch2D>();
	m_glowingParticles->init(1000, 0.05f, ResourceManager::getTexture("Textures/glow_particle.png"));
	m_particleEngine.addParticleBatch(m_glowingParticles.get());

	m_audioEngine.init();
	Music backgroungMusic = m_audioEngine.loadMusic("Sounds/calm_bgm.ogg");
	backgroungMusic.play(-1);

	loadMeshes();
	initShaders();
}

void MainApp::addScreens() {
	m_gameplayScreen = std::make_unique<GameplayScreen>();

	m_screenList->addScreen(m_gameplayScreen.get());
	m_screenList->setScreen(m_gameplayScreen->getScreenIndex());
}

void MainApp::onExit() {

}

void MainApp::update() {
	IMainGame::update();

	m_particleEngine.update();
}

void MainApp::draw() {
	IMainGame::draw();
}

void MainApp::loadMeshes() {
	// Hacky way of initializing all models
	ResourceManager::getModel("Models/molecula_azucar.obj");
	ResourceManager::getModel("Models/molecula_agua.obj");
	ResourceManager::getModel("Models/molecula_dioxidoC.obj");
	ResourceManager::getModel("Models/molecula_metano.obj");
	ResourceManager::getModel("Models/molecula_oxido.obj");
	ResourceManager::getModel("Models/molecula_acdoS.obj");
}

void MainApp::initShaders() {
	m_spriteShader.compileShaders("Shaders/spriteShader.vert", "Shaders/spriteShader.frag");
	m_spriteShader.addAttribute("vertexPosition");
	m_spriteShader.addAttribute("vertexColor");
	m_spriteShader.addAttribute("vertexUV");
	m_spriteShader.linkShaders();

	m_meshShader.compileShaders("Shaders/meshShader.vert", "Shaders/meshShader.frag");
	m_meshShader.addAttribute("vertexPosition");
	m_meshShader.addAttribute("vertexUV");
	m_meshShader.addAttribute("vertexNormal");
	m_meshShader.linkShaders();
}