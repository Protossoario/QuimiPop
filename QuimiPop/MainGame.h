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
#include <OpenGL/gl3.h>
#include <random>
#include "glm/glm.hpp"
#include "glm/gtx/rotate_vector.hpp"
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
    void calculateFPS();
    void addGlow(const glm::vec2& position, int numParticles);
    
    Window _window;
    int _screenWidth;
    int _screenHeight;
    GameState _gameState;
        
    GLSLProgram _colorProgram;
    Camera2D _camera;
    
    SpriteBatch _spriteBatch;
    ParticleEngine2D _particleEngine;
    ParticleBatch2D* _particleBatch;
    
    InputManager _inputManager;
    FPSLimiter _fpsLimiter;
    
    GameBoard _gameBoard;
    
    float _fps;
    float _maxFPS;
};

#endif /* defined(__GraphicsTutorial__MainGame__) */
