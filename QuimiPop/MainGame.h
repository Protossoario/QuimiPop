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
#include "glm/glm.hpp"
#include "Errors.h"
#include "GLSLProgram.h"
#include "Window.h"
#include "Camera2D.h"
#include "SpriteBatch.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "Timing.h"
#include "GameBoard.h"

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
    
    Window _window;
    int _screenWidth;
    int _screenHeight;
    GameState _gameState;
        
    GLSLProgram _colorProgram;
    Camera2D _camera;
    
    SpriteBatch _spriteBatch;
    
    InputManager _inputManager;
    FPSLimiter _fpsLimiter;
    
    GameBoard _gameBoard;
    
    float _fps;
    float _maxFPS;
};

#endif /* defined(__GraphicsTutorial__MainGame__) */
