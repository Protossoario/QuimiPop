//
//  MainGame.cpp
//  GraphicsTutorial
//
//  Created by Eduardo Alberto Sanchez Alvarado & Graciela Garcia Diaz on 3/1/15.
//  Copyright (c) 2015 Eduardo Alberto Sanchez Alvarado & Graciela Garcia Diaz. All rights reserved.
//

#include "MainGame.h"

MainGame::MainGame() : m_screenWidth(1024), m_screenHeight(720), m_gameState(GameState::PLAY), m_maxFPS(60.0f), m_gameBoard(glm::vec2(-450.0f, -300.0f)) {
    m_camera.init(m_screenWidth, m_screenHeight);
    m_gameBoard.init();
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
    
    m_window.create("ChemiPop", m_screenWidth, m_screenHeight, 0);
    
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
    
    m_spriteBatch.init();
    
    m_fpsLimiter.init(m_maxFPS);
    
    m_particleBatch = new ParticleBatch2D;
    m_particleBatch->init(1000, 0.05f, ResourceManager::getTexture("/Users/EduardoS/Documents/Programacion/XCode Projects/QuimiPop/QuimiPop/Textures/glow_particle.png"));
    m_particleEngine.addParticleBatch(m_particleBatch);
}

void MainGame::initShaders() {
    m_colorProgram.compileShaders("/Users/EduardoS/Documents/Programacion/XCode Projects/GraphicsTutorial/GraphicsTutorial/Shaders/colorShading.vert", "/Users/EduardoS/Documents/Programacion/XCode Projects/GraphicsTutorial/GraphicsTutorial/Shaders/colorShading.frag");
    m_colorProgram.addAttribute("vertexPosition");
    m_colorProgram.addAttribute("vertexColor");
    m_colorProgram.addAttribute("vertexUV");
    m_colorProgram.linkShaders();
}

void MainGame::gameLoop() {
    while (m_gameState != GameState::EXIT) {
        m_fpsLimiter.begin();
        
        processInput();
        
        m_camera.update();
        m_gameBoard.update();
        m_particleEngine.update();
        
        drawGame();
        
        m_fps = m_fpsLimiter.end();
        
        static int frameCounter = 0;
        frameCounter++;
        if (frameCounter == 1000) {
            printf("FPS: %.1f\n", m_fps);
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
                m_gameState = GameState::EXIT;
                break;
                
            case SDL_MOUSEMOTION:
                m_inputManager.setMouseCoords(ev.motion.x, ev.motion.y);
                break;
                
            case SDL_KEYDOWN:
                m_inputManager.pressKey(ev.key.keysym.sym);
                break;
            
            case SDL_KEYUP:
                m_inputManager.releaseKey(ev.key.keysym.sym);
                break;
                
            case SDL_MOUSEBUTTONDOWN:
                m_inputManager.pressKey(ev.button.button);
                break;
                
            case SDL_MOUSEBUTTONUP:
                m_inputManager.releaseKey(ev.button.button);
                break;
        }
    }
    
    if (m_inputManager.isKeyPressed(SDLK_w)) {
        m_camera.setPosition(m_camera.getPosition() + glm::vec2(0.0f, CAMERA_SPEED));
    }
    if (m_inputManager.isKeyPressed(SDLK_s)) {
        m_camera.setPosition(m_camera.getPosition() + glm::vec2(0.0f, -CAMERA_SPEED));
    }
    if (m_inputManager.isKeyPressed(SDLK_a)) {
        m_camera.setPosition(m_camera.getPosition() + glm::vec2(-CAMERA_SPEED, 0.0f));
    }
    if (m_inputManager.isKeyPressed(SDLK_d)) {
        m_camera.setPosition(m_camera.getPosition() + glm::vec2(CAMERA_SPEED, 0.0f));
    }
    if (m_inputManager.isKeyPressed(SDLK_q)) {
        m_camera.setScale(m_camera.getScale() + SCALE_SPEED);
    }
    if (m_inputManager.isKeyPressed(SDLK_e)) {
        m_camera.setScale(m_camera.getScale() - SCALE_SPEED);
    }
    if (m_inputManager.isKeyPressed(SDL_BUTTON_LEFT)) {
        glm::vec2 mouseCoords = m_inputManager.getMouseCoords();
        mouseCoords = m_camera.convertScreenToWorld(mouseCoords);
        
        if (m_gameBoard.isPointInsideBoard(mouseCoords)) {
            m_gameBoard.setClickingDown(true);
            m_gameBoard.updateMouseCoords(mouseCoords);
        }
        
        addGlow(mouseCoords, 10);
    }
    else {
        glm::vec2 mouseCoords = m_inputManager.getMouseCoords();
        mouseCoords = m_camera.convertScreenToWorld(mouseCoords);
        
        if (m_gameBoard.isPointInsideBoard(mouseCoords)) {
            m_gameBoard.setClickingDown(false);
        }
    }
}

void MainGame::drawGame() {
    glClearDepth(1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    m_colorProgram.use();
    
    glActiveTexture(GL_TEXTURE0);
    GLint textureLocation = m_colorProgram.getUniformLocation("mySampler");
    glUniform1i(textureLocation, 0);
    
    GLint pLocation = m_colorProgram.getUniformLocation("P");
    glm::mat4 cameraMatrix = m_camera.getCameraMatrix();
    glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));
    
    m_spriteBatch.begin();
    
    glm::vec4 backgroundRect(-m_screenWidth / 2, -m_screenHeight / 2, m_screenWidth, m_screenHeight);
    glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
    static GLTexture backgroundTexture = ResourceManager::getTexture("/Users/EduardoS/Documents/Programacion/XCode Projects/QuimiPop/QuimiPop/Textures/Background.png");
    ColorRGBA8 color(255, 255, 255, 255);
    m_spriteBatch.draw(backgroundRect, uvRect, backgroundTexture.textureId, 0.0f, color);
    
    m_gameBoard.draw(m_spriteBatch);
    
    m_spriteBatch.end();
    
    m_spriteBatch.renderBatch();
    
    m_particleEngine.draw(&m_spriteBatch);
    
    glBindTexture(GL_TEXTURE_2D, 0);
    
    m_colorProgram.unuse();
    
    m_window.swapBuffer();
}

void MainGame::addGlow(const glm::vec2 &position, int numParticles) {
    static std::mt19937 randEngine(time(nullptr));
    static std::uniform_real_distribution<float> randAngle(0.0f, 360.0f);
    
    glm::vec2 vel(1.0f, 0.0f);
    ColorRGBA8 col(255, 255, 255, 255);
    
    for (int i = 0; i < numParticles; i++) {
        m_particleBatch->addParticle(position, glm::rotate(vel, randAngle(randEngine)), col, 10.0f);
    }
}