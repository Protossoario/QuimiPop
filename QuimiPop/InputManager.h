//
//  InputManager.h
//  GraphicsTutorial
//
//  Created by Eduardo Alberto Sanchez Alvarado & Graciela Garcia Diaz on 3/21/15.
//  Copyright (c) 2015 Eduardo Alberto Sanchez Alvarado & Graciela Garcia Diaz. All rights reserved.
//

#ifndef __GraphicsTutorial__InputManager__
#define __GraphicsTutorial__InputManager__

#include <unordered_map>
#include "glm/glm.hpp"

class InputManager {
public:
    InputManager();

	void update();
    
    void pressKey(unsigned int keyID);
    void releaseKey(unsigned int keyID);

	// Returns true if the key is held down
    bool isKeyDown(unsigned int keyID);
	// Returns true if the key was just pressed
	bool isKeyPressed(unsigned int keyID);

    void setMouseCoords(float x, float y);
    glm::vec2 getMouseCoords() const { return m_mouseCoords; }
    
private:
	// Returns true if the key was pressed last frame
	bool wasKeyDown(unsigned int keyID);

    std::unordered_map<unsigned int, bool> m_keyMap;
	std::unordered_map<unsigned int, bool> m_previousKeyMap;
    glm::vec2 m_mouseCoords;
};

#endif /* defined(__GraphicsTutorial__InputManager__) */
