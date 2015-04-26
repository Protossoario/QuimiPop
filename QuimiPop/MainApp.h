#pragma once

#include "IMainGame.h"
#include "GameplayScreen.h"
#include "SpriteFont.h"
#include "ParticleBatch2D.h"
#include "ParticleEngine2D.h"
#include "AudioEngine.h"
#include "GLSLProgram.h"

class MainApp : public IMainGame {
public:
	friend GameplayScreen;

	MainApp();
	~MainApp();

	virtual void onInit() override;
	virtual void addScreens() override;
	virtual void onExit() override;

private:
	void update();
	void draw();

	void loadMeshes();
	void initShaders();

	std::unique_ptr<GameplayScreen> m_gameplayScreen = nullptr;
	std::unique_ptr<SpriteFont> m_hudFont = nullptr;

	ParticleEngine2D m_particleEngine;
	std::unique_ptr<ParticleBatch2D> m_glowingParticles = nullptr;

	AudioEngine m_audioEngine;

	GLSLProgram m_spriteShader;
	GLSLProgram m_meshShader;
};

