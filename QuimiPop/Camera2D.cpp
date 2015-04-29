//
//  Camera2D.cpp
//  GraphicsTutorial
//
//  Created by Eduardo Alberto Sanchez Alvarado & Graciela Garcia Diaz on 3/21/15.
//  Copyright (c) 2015 Eduardo Alberto Sanchez Alvarado & Graciela Garcia Diaz. All rights reserved.
//

#include "Camera2D.h"

Camera2D::Camera2D() : m_position(0, 0), m_cameraMatrix(1.0f), m_orthoMatrix(1.0f), m_scale(1.0f), m_needsMatrixUpdate(true), m_screenWidth(500), m_screenHeight(500) {}

void Camera2D::init(int screenWidth, int screenHeight) {
    m_screenWidth = screenWidth;
    m_screenHeight = screenHeight;
    m_orthoMatrix = glm::ortho(0.0f, (float)m_screenWidth, 0.0f, (float)m_screenHeight, -1000.0f, 1000.0f);
}

void Camera2D::update() {
    if (m_needsMatrixUpdate) {
        glm::vec3 translate(m_screenWidth / 2 - m_position.x, m_screenHeight / 2 - m_position.y, 0.0f);
        m_cameraMatrix = glm::translate(m_orthoMatrix, translate);
        
        glm::vec3 scale(m_scale, m_scale, m_scale);
        m_cameraMatrix = glm::scale(glm::mat4(1.0f), scale) * m_cameraMatrix;
        
        m_needsMatrixUpdate = false;
    }
}

glm::vec2 Camera2D::convertScreenToWorld(glm::vec2 screenCoords) {
    // invert Y-axis
    screenCoords.y = m_screenHeight - screenCoords.y;
    // make 0 the center
    screenCoords -= glm::vec2(m_screenWidth / 2, m_screenHeight / 2);
    // scale the coordinates
    screenCoords /= m_scale;
    // translate with the camera position
    screenCoords += m_position;
    
    return screenCoords;
}