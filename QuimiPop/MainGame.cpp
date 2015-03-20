//
//  MainGame.cpp
//  GraphicsTutorial
//
//  Created by Eduardo Alberto Sanchez Alvarado on 3/1/15.
//  Copyright (c) 2015 Eduardo Alberto Sanchez Alvarado. All rights reserved.
//

#include "MainGame.h"
#include <stdlib.h>
#include <time.h>

MainGame::MainGame() : _window(nullptr), _screenWidth(500), _screenHeight(500), _gameState(GameState::PLAY), _time(0), _maxFPS(60.0f) {}

MainGame::~MainGame() {}

std::string spriteNameForIndex(int index) {
    switch (index) {
        case 0:
            return "blue_gem.png";
            break;
            
        case 1:
            return "gray_gem.png";
            break;
            
        case 2:
            return "light_blue_gem.png";
            break;
            
        case 3:
            return "orange_gem.png";
            break;
            
        case 4:
            return "purple_gem.png";
            break;
            
        case 5:
            return "red_gem.png";
            break;
            
        case 6:
            return "teal_gem.png";
            break;
            
        case 7:
            return "yellow_gem.png";
            break;
            
        default:
            return "blue_gem.png";
            break;
    }
}

void MainGame::run() {
    initSystems();
    
    srand(time(NULL));
    
    std::string basePath = "/Users/EduardoS/Documents/Programacion/XCode Projects/QuimiPop/QuimiPop/Textures/";
    float x = -1.0;
    float y = -1.0;
    for (int col = 0; col < 10; col++) {
        for (int row = 0; row < 10; row++) {
            int spriteIndex = rand() % 8;
            _sprites.push_back(new Sprite());
            _sprites.back()->init(x, y, 0.20, 0.20, basePath + spriteNameForIndex(spriteIndex));
            x += 0.20;
        }
        y += 0.20;
        x = -1.0;
    }
    
    gameLoop();
}

void MainGame::initSystems() {
    // Initialize SDL
    SDL_Init(SDL_INIT_EVERYTHING);
    
    // Required for Mac OS X to support GLSL version 130 or higher
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    
    _window = SDL_CreateWindow("Game Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight, SDL_WINDOW_OPENGL);
    
    if (_window == nullptr) {
        fatalError("SDL Window could not be created!");
    }
    
    SDL_GLContext glContext = SDL_GL_CreateContext(_window);
    if (glContext == nullptr) {
        fatalError("SDL GL Context could not be created!");
    }
    
    // Required for Mac OS X
    GLuint vertexArrayID;
    glGenVertexArrays(1, &vertexArrayID);
    if (vertexArrayID == 0) {
        printf("%s\n", gluErrorString(glGetError()));
        fatalError("Could not generate Vertex Array Object!");
    }
    glBindVertexArray(vertexArrayID);
    
    printf("OpenGL version %s\n", glGetString(GL_VERSION));
    printf("GLSL version %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
    
    // Turn on double buffering
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    
    initShaders();
}

void MainGame::initShaders() {
    _colorProgram.compileShaders("/Users/EduardoS/Documents/Programacion/XCode Projects/QuimiPop/QuimiPop/Shaders/colorShading.vert", "/Users/EduardoS/Documents/Programacion/XCode Projects/QuimiPop/QuimiPop/Shaders/colorShading.frag");
    _colorProgram.addAttribute("vertexPosition");
    _colorProgram.addAttribute("vertexColor");
    _colorProgram.addAttribute("vertexUV");
    _colorProgram.linkShaders();
}

void MainGame::gameLoop() {
    while (_gameState != GameState::EXIT) {
        float startTicks = SDL_GetTicks();
        
        processInput();
        _time += 0.05;
        drawGame();
        calculateFPS();
        
        static int frameCounter = 0;
        frameCounter++;
        if (frameCounter == 10) {
            printf("FPS: %.1f\n", _fps);
            frameCounter = 0;
        }
        
        float frameTicks = SDL_GetTicks() - startTicks;
        if (1000.0f / _maxFPS > frameTicks) {
            SDL_Delay(1000.0f / _maxFPS - frameTicks);
        }
    }
}

void MainGame::processInput() {
    SDL_Event ev;
    while (SDL_PollEvent(&ev)) {
        switch (ev.type) {
            case SDL_QUIT:
                _gameState = GameState::EXIT;
                break;
                
            case SDL_MOUSEMOTION:
                printf("x: %d y: %d\n", ev.motion.x, ev.motion.y);
                break;
        }
    }
}

void MainGame::drawGame() {
    glClearDepth(1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    _colorProgram.use();
    
    glActiveTexture(GL_TEXTURE0);
    GLint textureLocation = _colorProgram.getUniformLocation("mySampler");
    glUniform1i(textureLocation, 0);
    
    GLint timeLocation = _colorProgram.getUniformLocation("time");
    glUniform1f(timeLocation, _time);
    
    for (int i = 0; i < _sprites.size(); i++) {
        _sprites[i]->draw();
    }
    
    glBindTexture(GL_TEXTURE_2D, 0);
    
    _colorProgram.unuse();
    
    SDL_GL_SwapWindow(_window);
}

void MainGame::calculateFPS() {
    static const int NUM_SAMPLES = 10;
    static float frameTimes[NUM_SAMPLES];
    static int currentFrame = 0;
    
    static float prevTicks = SDL_GetTicks();
    
    float currentTicks;
    currentTicks = SDL_GetTicks();
    
    _frameTime = currentTicks - prevTicks;
    
    frameTimes[currentFrame % NUM_SAMPLES] = _frameTime;
    
    prevTicks = currentTicks;
    
    int count;
    
    currentFrame++;
    if (currentFrame < NUM_SAMPLES) {
        count = currentFrame;
    }
    else {
        count = NUM_SAMPLES;
    }
    
    float frameTimeAverage = 0;
    for (int i = 0; i < count; i++) {
        frameTimeAverage += frameTimes[i];
    }
    frameTimeAverage /= count;
    
    if (frameTimeAverage > 0) {
        _fps = 1000.0f / frameTimeAverage;
    }
    else {
        _fps = 60.0f;
    }
}