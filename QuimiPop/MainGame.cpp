//
//  MainGame.cpp
//  GraphicsTutorial
//
//  Created by Eduardo Alberto Sanchez Alvarado on 3/1/15.
//  Copyright (c) 2015 Eduardo Alberto Sanchez Alvarado. All rights reserved.
//

#include "MainGame.h"

MainGame::MainGame() : _screenWidth(1024), _screenHeight(720), _gameState(GameState::PLAY), _maxFPS(60.0f), _gameBoard(glm::vec2(-450.0f, -300.0f)) {
    _camera.init(_screenWidth, _screenHeight);
    _gameBoard.init();
}

MainGame::~MainGame() {}

void MainGame::run() {
    initSystems();
    
    gameLoop();
}

void MainGame::initSystems() {
    // Initialize SDL
    SDL_Init(SDL_INIT_EVERYTHING);
    
    // Required for Mac OS X to support GLSL version 130 or higher
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    
    _window.create("ChemiPop", _screenWidth, _screenHeight, 0);
    
    // Required for Mac OS X
    GLuint vertexArrayID;
    glGenVertexArrays(1, &vertexArrayID);
    if (vertexArrayID == 0) {
        fatalError("Could not generate Vertex Array Object!");
    }
    glBindVertexArray(vertexArrayID);
    
    printf("OpenGL version %s\n", glGetString(GL_VERSION));
    printf("GLSL version %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
    
    initShaders();
    
    _spriteBatch.init();
    
    _fpsLimiter.init(_maxFPS);
}

void MainGame::initShaders() {
    _colorProgram.compileShaders("/Users/EduardoS/Documents/Programacion/XCode Projects/GraphicsTutorial/GraphicsTutorial/Shaders/colorShading.vert", "/Users/EduardoS/Documents/Programacion/XCode Projects/GraphicsTutorial/GraphicsTutorial/Shaders/colorShading.frag");
    _colorProgram.addAttribute("vertexPosition");
    _colorProgram.addAttribute("vertexColor");
    _colorProgram.addAttribute("vertexUV");
    _colorProgram.linkShaders();
}

void MainGame::gameLoop() {
    while (_gameState != GameState::EXIT) {
        _fpsLimiter.begin();
        
        processInput();
        
        _camera.update();
        
        drawGame();
        
        _fps = _fpsLimiter.end();
        
        static int frameCounter = 0;
        frameCounter++;
        if (frameCounter == 1000) {
            printf("FPS: %.1f\n", _fps);
            frameCounter = 0;
        }
    }
}

void MainGame::processInput() {
    const float CAMERA_SPEED = 5.0f;
    const float SCALE_SPEED = 0.01f;
    
    SDL_Event ev;
    while (SDL_PollEvent(&ev)) {
        switch (ev.type) {
            case SDL_QUIT:
                _gameState = GameState::EXIT;
                break;
                
            case SDL_MOUSEMOTION:
                _inputManager.setMouseCoords(ev.motion.x, ev.motion.y);
                break;
                
            case SDL_KEYDOWN:
                _inputManager.pressKey(ev.key.keysym.sym);
                break;
            
            case SDL_KEYUP:
                _inputManager.releaseKey(ev.key.keysym.sym);
                break;
                
            case SDL_MOUSEBUTTONDOWN:
                _inputManager.pressKey(ev.button.button);
                break;
                
            case SDL_MOUSEBUTTONUP:
                _inputManager.releaseKey(ev.button.button);
                break;
        }
    }
    
    if (_inputManager.isKeyPressed(SDLK_w)) {
        _camera.setPosition(_camera.getPosition() + glm::vec2(0.0f, CAMERA_SPEED));
    }
    if (_inputManager.isKeyPressed(SDLK_s)) {
        _camera.setPosition(_camera.getPosition() + glm::vec2(0.0f, -CAMERA_SPEED));
    }
    if (_inputManager.isKeyPressed(SDLK_a)) {
        _camera.setPosition(_camera.getPosition() + glm::vec2(-CAMERA_SPEED, 0.0f));
    }
    if (_inputManager.isKeyPressed(SDLK_d)) {
        _camera.setPosition(_camera.getPosition() + glm::vec2(CAMERA_SPEED, 0.0f));
    }
    if (_inputManager.isKeyPressed(SDLK_q)) {
        _camera.setScale(_camera.getScale() + SCALE_SPEED);
    }
    if (_inputManager.isKeyPressed(SDLK_e)) {
        _camera.setScale(_camera.getScale() - SCALE_SPEED);
    }
    if (_inputManager.isKeyPressed(SDL_BUTTON_LEFT)) {
        glm::vec2 mouseCoords = _inputManager.getMouseCoords();
        mouseCoords = _camera.convertScreenToWorld(mouseCoords);
        
        _gameBoard.setClickingDown(true);
        _gameBoard.updateMouseCoords(mouseCoords);
    }
    else {
        _gameBoard.setClickingDown(false);
    }
}

void MainGame::drawGame() {
    glClearDepth(1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    _colorProgram.use();
    
    glActiveTexture(GL_TEXTURE0);
    GLint textureLocation = _colorProgram.getUniformLocation("mySampler");
    glUniform1i(textureLocation, 0);
    
    GLint pLocation = _colorProgram.getUniformLocation("P");
    glm::mat4 cameraMatrix = _camera.getCameraMatrix();
    glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));
    
    _spriteBatch.begin();
    
    glm::vec4 backgroundRect(-_screenWidth / 2, -_screenHeight / 2, _screenWidth, _screenHeight);
    glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
    static GLTexture backgroundTexture = ResourceManager::getTexture("/Users/EduardoS/Documents/Programacion/XCode Projects/QuimiPop/QuimiPop/Textures/Background.png");
    Color color;
    color.r = 255;
    color.g = 255;
    color.b = 255;
    color.a = 255;
    _spriteBatch.draw(backgroundRect, uvRect, backgroundTexture.textureId, 0.0f, color);
    
    _gameBoard.draw(_spriteBatch);
    
    _spriteBatch.end();
    
    _spriteBatch.renderBatch();
    
    glBindTexture(GL_TEXTURE_2D, 0);
    
    _colorProgram.unuse();
    
    _window.swapBuffer();
}