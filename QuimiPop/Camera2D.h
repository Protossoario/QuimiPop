//
//  Camera2D.h
//  GraphicsTutorial
//
//  Created by Eduardo Alberto Sanchez Alvarado & Graciela Garcia Diaz on 3/21/15.
//  Copyright (c) 2015 Eduardo Alberto Sanchez Alvarado & Graciela Garcia Diaz. All rights reserved.
//

#ifndef __GraphicsTutorial__Camera2D__
#define __GraphicsTutorial__Camera2D__

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Camera2D {
public:
    Camera2D();
    
    void init(int screenWidth, int screenHeight);
    
    void update();
    
    glm::vec2 convertScreenToWorld(glm::vec2 screenCoords);
    
    // setters
    void setPosition(glm::vec2 newPosition) { m_position = newPosition; m_needsMatrixUpdate = true; }
    void setScale(float newScale) { m_scale = newScale; m_needsMatrixUpdate = true; }
    
    // getters
    glm::vec2 getPosition() { return m_position; }
    float getScale() { return m_scale; }
    glm::mat4 getCameraMatrix() { return m_cameraMatrix; }
    
private:
    bool m_needsMatrixUpdate;
    int m_screenWidth, m_screenHeight;
    float m_scale;
    glm::vec2 m_position;
    glm::mat4 m_cameraMatrix;
    glm::mat4 m_orthoMatrix;
};

#endif /* defined(__GraphicsTutorial__Camera2D__) */
