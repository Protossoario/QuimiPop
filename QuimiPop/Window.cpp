//
//  Window.cpp
//  GraphicsTutorial
//
//  Created by Eduardo Alberto Sanchez Alvarado & Graciela Garcia Diaz on 3/21/15.
//  Copyright (c) 2015 Eduardo Alberto Sanchez Alvarado & Graciela Garcia Diaz. All rights reserved.
//

#include "Window.h"

Window::Window() : m_sdlWindow(nullptr) {}

int Window::create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags) {
    Uint32 flags = SDL_WINDOW_OPENGL;
    
    if (currentFlags & INVISIBLE) {
        flags |= SDL_WINDOW_HIDDEN;
    }
    
    if (currentFlags & FULLSCREEN) {
        flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
    }
    
    if (currentFlags & BORDERLESS) {
		flags |= SDL_WINDOW_BORDERLESS;
    }
    
    m_sdlWindow = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, flags);
    
    if (m_sdlWindow == nullptr) {
        const char *error = SDL_GetError();
        printf("Error: %s\n", error);
        fatalError("SDL Window could not be created!");
    }
    
    SDL_GLContext glContext = SDL_GL_CreateContext(m_sdlWindow);
    if (glContext == nullptr) {
        fatalError("SDL GL Context could not be created!");
    }
    
	GLenum error = glewInit();
	if (error != GLEW_OK) {
		fatalError("Could not initialized glew!");
	}

    glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
    
    // Turn on double buffering
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    // Set VSync off
    SDL_GL_SetSwapInterval(0);
    // Enabled alpha blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);
    
    return 0;
}

void Window::swapBuffer() {
    SDL_GL_SwapWindow(m_sdlWindow);
}