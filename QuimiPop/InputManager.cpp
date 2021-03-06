//
//  InputManager.cpp
//  GraphicsTutorial
//
//  Created by Eduardo Alberto Sanchez Alvarado & Graciela Garcia Diaz on 3/21/15.
//  Copyright (c) 2015 Eduardo Alberto Sanchez Alvarado & Graciela Garcia Diaz. All rights reserved.
//

#include "InputManager.h"

InputManager::InputManager() : m_mouseCoords(0.0f, 0.0f) {}

void InputManager::pressKey(unsigned int keyID) {
    m_keyMap[keyID] = true;
}

void InputManager::releaseKey(unsigned int keyID) {
    m_keyMap[keyID] = false;
}

bool InputManager::isKeyDown(unsigned int keyID) {
    auto it = m_keyMap.find(keyID);
    if (it != m_keyMap.end()) {
        return m_keyMap[keyID];
    }
    return false;
}

void InputManager::setMouseCoords(float x, float y) {
    m_mouseCoords.x = x;
    m_mouseCoords.y = y;
}