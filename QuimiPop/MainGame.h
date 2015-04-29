//
//  MainGame.h
//  GraphicsTutorial
//
//  Created by Eduardo Alberto Sanchez Alvarado & Graciela Garcia Diaz on 3/1/15.
//  Copyright (c) 2015 Eduardo Alberto Sanchez Alvarado & Graciela Garcia Diaz. All rights reserved.
//

#ifndef __GraphicsTutorial__MainGame__
#define __GraphicsTutorial__MainGame__

#include <SDL2/SDL.h>
//#include <OpenGL/gl3.h>
#include <Windows.h>
#include <GL/glew.h>
#include <random>
#include <map>
#include "glm/glm.hpp"
#include "glm/gtx/rotate_vector.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Errors.h"
#include "GLSLProgram.h"
#include "Window.h"
#include "Camera2D.h"
#include "SpriteBatch.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "Timing.h"
#include "GameBoard.h"
#include "ParticleEngine2D.h"
#include "ParticleBatch2D.h"
#include "Mesh.h"
#include "SpriteFont.h"
#include "AudioEngine.h"

enum class GameState { PLAY, EXIT };

class MainGame {
public:
    MainGame();
    ~MainGame();
    
    void run();
    
private:
    void initSystems();
    void initShaders();
    void gameLoop();
    void processInput();
    void drawGame();
	void drawHUD();
	void drawTitleScreen();
    void calculateFPS();
    void addGlow(const glm::vec2& position, int numParticles);
    
    Window m_window;
    int m_screenWidth;
    int m_screenHeight;
    GameState m_gameState;
        
    GLSLProgram m_spriteShader;
	GLSLProgram m_meshShader;
    Camera2D m_camera;
    
    SpriteBatch m_spriteBatch;
	SpriteBatch m_hudBatch;
    ParticleEngine2D m_particleEngine;
    ParticleBatch2D* m_particleBatch;

	SpriteFont* m_spriteFont;

	AudioEngine m_audioEngine;

	std::map<Molecule, Mesh> m_molecules;
    
    InputManager m_inputManager;
    FPSLimiter m_fpsLimiter;
    
    GameBoard m_gameBoard;
    
    float m_fps;
    float m_maxFPS;

	float m_angle;

	bool m_showingTitle = true;
	bool m_showingCredits = false;
	bool m_showingInstructions = false;

	float m_sidebarOffsetY = 0.0f;
};

#endif /* defined(__GraphicsTutorial__MainGame__) */
