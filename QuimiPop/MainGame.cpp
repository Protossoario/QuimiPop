//
//  MainGame.cpp
//  GraphicsTutorial
//
//  Created by Eduardo Alberto Sanchez Alvarado & Graciela Garcia Diaz on 3/1/15.
//  Copyright (c) 2015 Eduardo Alberto Sanchez Alvarado & Graciela Garcia Diaz. All rights reserved.
//

#include "MainGame.h"

MainGame::MainGame() : m_screenWidth(960), m_screenHeight(540), m_gameState(GameState::PLAY), m_maxFPS(60.0f), m_gameBoard(glm::vec2(-425.0f, -250.0f)), m_angle(0.0f) {
    m_camera.init(m_screenWidth, m_screenHeight);
    m_gameBoard.init();
}

MainGame::~MainGame() {
	delete m_spriteFont;
}

void MainGame::run() {
    initSystems();

	Music bgMusic = m_audioEngine.loadMusic("Sounds/calm_bgm.ogg");
	bgMusic.play(-1);
    
    gameLoop();
}

void MainGame::initSystems() {
    // Initialize SDL
    SDL_Init(SDL_INIT_EVERYTHING);
    
    // Required for Mac OS X to support GLSL version 130 or higher
    //SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    
    m_window.create("QuimiPop", m_screenWidth, m_screenHeight, 0);
	/*
    // Required for Mac OS X
    GLuint vertexArrayID;
    glGenVertexArrays(1, &vertexArrayID);
    if (vertexArrayID == 0) {
        fatalError("Could not generate Vertex Array Object!");
    }
    glBindVertexArray(vertexArrayID);
	*/
    printf("OpenGL version %s\n", glGetString(GL_VERSION));
    printf("GLSL version %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

	m_audioEngine.init();

	SoundEffect moleculeSound = m_audioEngine.loadSoundEffect("Sounds/Item1B.wav");
	m_gameBoard.setMoleculeSound(moleculeSound);
    
    initShaders();
    
    m_spriteBatch.init();
	m_hudBatch.init();

	m_spriteFont = new SpriteFont("Fonts/chemistry.ttf", 32);
    
    m_fpsLimiter.init(m_maxFPS);
    
    m_particleBatch = new ParticleBatch2D;
    m_particleBatch->init(1000, 0.05f, ResourceManager::getTexture("Textures/glow_particle.png"));
    m_particleEngine.addParticleBatch(m_particleBatch);

	m_molecules.insert(std::make_pair(SUGAR, Mesh()));
	m_molecules.find(SUGAR)->second.loadMesh("Models/molecula_azucar.obj");

	m_molecules.insert(std::make_pair(WATER, Mesh()));
	m_molecules.find(WATER)->second.loadMesh("Models/molecula_agua.obj");

	m_molecules.insert(std::make_pair(CARBON_DIOXIDE, Mesh()));
	m_molecules.find(CARBON_DIOXIDE)->second.loadMesh("Models/molecula_dioxidoC.obj");

	m_molecules.insert(std::make_pair(METHANE, Mesh()));
	m_molecules.find(METHANE)->second.loadMesh("Models/molecula_metano.obj");

	m_molecules.insert(std::make_pair(NITROUS_OXIDE, Mesh()));
	m_molecules.find(NITROUS_OXIDE)->second.loadMesh("Models/molecula_oxido.obj");

	m_molecules.insert(std::make_pair(SULFURIC_ACID, Mesh()));
	m_molecules.find(SULFURIC_ACID)->second.loadMesh("Models/molecula_acdoS.obj");
}

void MainGame::initShaders() {
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

void MainGame::gameLoop() {
    while (m_gameState != GameState::EXIT) {
        m_fpsLimiter.begin();
        
		m_inputManager.update();
        processInput();

		m_angle += 0.025f;
		if (m_angle >= 360.0f) {
			m_angle = 0.0f;
		}
        
		m_camera.update();

		if (m_gameBoard.getRemainingTurns() == 0) {
			m_showingTitle = true;
			m_showingCredits = true;
		}

		if (m_showingTitle) {
			drawTitleScreen();
		}
		else {
			m_gameBoard.update();
			m_particleEngine.update();

			drawGame();
		}
        
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
    
    if (m_inputManager.isKeyDown(SDLK_w)) {
        m_camera.setPosition(m_camera.getPosition() + glm::vec2(0.0f, CAMERA_SPEED));
    }
    if (m_inputManager.isKeyDown(SDLK_s)) {
        m_camera.setPosition(m_camera.getPosition() + glm::vec2(0.0f, -CAMERA_SPEED));
    }
    if (m_inputManager.isKeyDown(SDLK_a)) {
        m_camera.setPosition(m_camera.getPosition() + glm::vec2(-CAMERA_SPEED, 0.0f));
    }
    if (m_inputManager.isKeyDown(SDLK_d)) {
        m_camera.setPosition(m_camera.getPosition() + glm::vec2(CAMERA_SPEED, 0.0f));
    }
    if (m_inputManager.isKeyDown(SDLK_q)) {
        m_camera.setScale(m_camera.getScale() + SCALE_SPEED);
    }
    if (m_inputManager.isKeyDown(SDLK_e)) {
        m_camera.setScale(m_camera.getScale() - SCALE_SPEED);
    }
	if (m_showingTitle && !m_showingCredits && m_inputManager.isKeyPressed(SDLK_RETURN)) {
		printf("Pressed enter\n");
		if (!m_showingInstructions) {
			m_showingInstructions = true;
		}
		else {
			m_showingInstructions = false;
			m_showingTitle = false;
			printf("Starting game!\n");
		}
	}
	else if (m_showingTitle && m_showingInstructions && m_inputManager.isKeyPressed(SDLK_i)) {
		m_showingInstructions = false;
		m_showingTitle = false;
	}
	else if (m_showingCredits && m_inputManager.isKeyPressed(SDLK_RETURN)) {
		printf("Resetting game!\n");
		m_showingCredits = false;
		m_gameBoard.resetGame();
	}
	else if (!m_showingTitle) {
		if (m_inputManager.isKeyDown(SDL_BUTTON_LEFT)) {
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
				m_gameBoard.updateMouseCoords(mouseCoords);
			}
		}
		if (m_inputManager.isKeyDown(SDL_BUTTON_RIGHT)) {
			m_gameBoard.resetHoverMolecule();
		}
		if (m_inputManager.isKeyPressed(SDLK_i)) {
			if (!m_showingInstructions) {
				m_showingTitle = true;
				m_showingInstructions = true;
			}
		}
		else if (m_inputManager.isKeyPressed(SDLK_ESCAPE)) {
			m_showingTitle = true;
		}
	}
}

void MainGame::drawGame() {
    glClearDepth(1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
	glDisable(GL_DEPTH_TEST);
	// Drawing 2D sprites
    m_spriteShader.use();
    
    glActiveTexture(GL_TEXTURE0);
    GLint textureLocation = m_spriteShader.getUniformLocation("mySampler");
    glUniform1i(textureLocation, 0);
    
    GLint pLocation = m_spriteShader.getUniformLocation("P");
    glm::mat4 cameraMatrix = m_camera.getCameraMatrix();
    glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	m_spriteBatch.begin();
    
    glm::vec4 backgroundRect(-m_screenWidth / 2, -m_screenHeight / 2, m_screenWidth, m_screenHeight);
    glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
    static GLTexture backgroundTexture = ResourceManager::getTexture("Textures/Background.png");
    ColorRGBA8 color(255, 255, 255, 255);
	m_spriteBatch.draw(backgroundRect, uvRect, backgroundTexture.textureId, 0.0f, color);

    m_gameBoard.draw(m_spriteBatch);
    
    m_spriteBatch.end();
    
    m_spriteBatch.renderBatch();
    
	drawHUD();

    m_particleEngine.draw(&m_spriteBatch);
    
    glBindTexture(GL_TEXTURE_2D, 0);
    
    m_spriteShader.unuse();

	glEnable(GL_DEPTH_TEST);

	// Drawing 3D molecule mesh
	m_meshShader.use();

	static float moleculeScale = 35.0f;

	GLint projectionLocation = m_meshShader.getUniformLocation("projection");
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	glm::mat4 transform;
	transform = glm::translate(transform, glm::vec3(325.0f, m_sidebarOffsetY - 50.0f, 0.0f));
	transform = glm::scale(transform, glm::vec3(moleculeScale));
	transform = glm::rotate(transform, 45.0f, glm::vec3(0.0f, 0.0f, 1.0f));
	transform = glm::rotate(transform, m_angle, glm::vec3(1.0f, 1.0f, 0.0f));
	GLint transformLocation = m_meshShader.getUniformLocation("transform");
	glUniformMatrix4fv(transformLocation, 1, GL_FALSE, &(transform[0][0]));
	
	std::map<Molecule, Mesh>::iterator iter = m_molecules.find(m_gameBoard.getHoverMolecule());
	if (iter != m_molecules.end()) {
		iter->second.render(m_meshShader);
	}

	m_meshShader.unuse();
    
    m_window.swapBuffer();
}

void MainGame::drawHUD() {
	m_hudBatch.begin();

	Molecule mol = m_gameBoard.getHoverMolecule();
	std::vector<std::string> titles;
	std::vector<std::string> descriptions;
	std::string turns = "Te quedan " + std::to_string(m_gameBoard.getRemainingTurns()) + " turnos!";
	std::string score = std::to_string(m_gameBoard.getScore());
	ColorRGBA8 white(255, 255, 255, 255);

	switch (mol) {
	case SUGAR:
		titles.push_back("Glucosa");
		descriptions.push_back("C6H12O6");
		descriptions.push_back("Se encuentra en frutas");
		descriptions.push_back("y alimentos procesados!");
		break;

	case WATER:
		titles.push_back("Agua");
		descriptions.push_back("H2O");
		descriptions.push_back("Compuesto esencial para");
		descriptions.push_back("la vida, se encuentra");
		descriptions.push_back("en todos los seres vivos!");
		break;

	case CARBON_DIOXIDE:
		titles.push_back("Dioxido de");
		titles.push_back("Carbono");
		descriptions.push_back("CO2");
		descriptions.push_back("Gas principal del calentamiento");
		descriptions.push_back("global!");
		descriptions.push_back("Lo emitimos al exhalar,");
		descriptions.push_back("y lo producen los combustibles");
		descriptions.push_back("de los autos!");
		break;

	case METHANE:
		titles.push_back("Metano");
		descriptions.push_back("CH4");
		descriptions.push_back("Se produce naturalmente");
		descriptions.push_back("a partir de los deshechos");
		descriptions.push_back("de las bacterias!");
		descriptions.push_back("Es un hidrocarburo que");
		descriptions.push_back("constitu hasta el 97%");
		descriptions.push_back("del gas natural!");
		break;

	case NITROUS_OXIDE:
		titles.push_back("Dioxido de");
		titles.push_back("Nitrogeno");
		descriptions.push_back("NO2");
		descriptions.push_back("Gas toxico que afecta el");
		descriptions.push_back("sistema respiratorio!");
		descriptions.push_back("Se forma en la combustion");
		descriptions.push_back("a altas temperaturas");
		descriptions.push_back("en vehiculos y");
		descriptions.push_back("plantas electricas!");
		break;

	case SULFURIC_ACID:
		titles.push_back("Acido");
		titles.push_back("Sulfurico");
		descriptions.push_back("H2SO4");
		descriptions.push_back("Compuesto quimico");
		descriptions.push_back("altamente corrosivo!");
		descriptions.push_back("Encontrado en los");
		descriptions.push_back("fertilizantes!");
		break;

	case NONE:
		titles.push_back("Instrucciones");
		descriptions.push_back("Usa el raton para mover las piezas");
		glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
		GLint hydrogen = ResourceManager::getTexture("Textures/Hydrogen2.png").textureId;
		GLint oxygen = ResourceManager::getTexture("Textures/Oxygen3.png").textureId;
		GLint water = ResourceManager::getTexture("Textures/Agua.png").textureId;
		m_hudBatch.draw(glm::vec4(215.0f, 50.0f, 75.0f, 75.0f), uv, hydrogen, 0.0f, white);
		m_hudBatch.draw(glm::vec4(290.0f, 50.0f, 75.0f, 75.0f), uv, oxygen, 0.0f, white);
		m_hudBatch.draw(glm::vec4(365.0f, 50.0f, 75.0f, 75.0f), uv, hydrogen, 0.0f, white);
		m_spriteFont->draw(m_hudBatch, "=", glm::vec2(325.0f, -35.0f), glm::vec2(2.5), 0.0f, white, Justification::MIDDLE);
		m_hudBatch.draw(glm::vec4(290.0f, -100.0f, 75.0f, 75.0f), uv, water, 0.0f, white);
		break;
	}

	float coordY = 210.0f;
	for each (auto title in titles) {
		m_spriteFont->draw(m_hudBatch, title.c_str(), glm::vec2(325.0f, coordY), glm::vec2(1.0), 0.0f, white, Justification::MIDDLE);
		coordY -= 25.0f;
	}

	for each (auto description in descriptions)
	{
		m_spriteFont->draw(m_hudBatch, description.c_str(), glm::vec2(325.0f, coordY), glm::vec2(0.5), 0.0f, white, Justification::MIDDLE);
		coordY -= 20.0f;
	}

	m_sidebarOffsetY = coordY - 25.0f;

	m_spriteFont->draw(m_hudBatch, score.c_str(), glm::vec2(325.0f, -255.0f), glm::vec2(1.5), 0.0f, white, Justification::MIDDLE);
	m_spriteFont->draw(m_hudBatch, turns.c_str(), glm::vec2(325.0f, -135.0f), glm::vec2(0.75f), 0.0f, white, Justification::MIDDLE);

	m_hudBatch.end();
	m_hudBatch.renderBatch();
}

void MainGame::drawTitleScreen() {
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDisable(GL_DEPTH_TEST);
	// Drawing 2D sprites
	m_spriteShader.use();

	glActiveTexture(GL_TEXTURE0);
	GLint textureLocation = m_spriteShader.getUniformLocation("mySampler");
	glUniform1i(textureLocation, 0);

	GLint pLocation = m_spriteShader.getUniformLocation("P");
	glm::mat4 cameraMatrix = m_camera.getCameraMatrix();
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	m_spriteBatch.begin();

	glm::vec4 backgroundRect(-m_screenWidth / 2, -m_screenHeight / 2, m_screenWidth, m_screenHeight);
	glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	static GLTexture titleTexture;
	if (m_showingCredits) {
		titleTexture = ResourceManager::getTexture("Textures/QuimiCreditos.png");
	}
	else if (m_showingInstructions) {
		titleTexture = ResourceManager::getTexture("Textures/QuimiInstrucciones.png");
	}
	else {
		titleTexture = ResourceManager::getTexture("Textures/QuimiPop-MainTitle.png");
	}
	ColorRGBA8 color(255, 255, 255, 255);
	m_spriteBatch.draw(backgroundRect, uvRect, titleTexture.textureId, 0.0f, color);

	m_spriteBatch.end();

	m_spriteBatch.renderBatch();

	glBindTexture(GL_TEXTURE_2D, 0);

	m_spriteShader.unuse();

	if (!m_showingCredits && !m_showingInstructions) {
		glEnable(GL_DEPTH_TEST);

		// Drawing 3D molecule mesh
		m_meshShader.use();

		static float moleculeScale = 70.0f;

		GLint projectionLocation = m_meshShader.getUniformLocation("projection");
		glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

		glm::mat4 transform;
		transform = glm::translate(transform, glm::vec3(0.0f, -50.0f, 0.0f));
		transform = glm::scale(transform, glm::vec3(moleculeScale));
		transform = glm::rotate(transform, 45.0f, glm::vec3(0.0f, 0.0f, 1.0f));
		transform = glm::rotate(transform, m_angle, glm::vec3(1.0f, 1.0f, 0.0f));
		GLint transformLocation = m_meshShader.getUniformLocation("transform");
		glUniformMatrix4fv(transformLocation, 1, GL_FALSE, &(transform[0][0]));

		m_molecules.find(SUGAR)->second.render(m_meshShader);

		m_meshShader.unuse();
	}

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