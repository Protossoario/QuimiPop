//
//  Sprite.h
//  QuimiPop
//
//  Created by Eduardo Alberto Sanchez Alvarado on 4/4/15.
//  Copyright (c) 2015 Eduardo Alberto Sanchez Alvarado. All rights reserved.
//

#ifndef __QuimiPop__Sprite__
#define __QuimiPop__Sprite__

#include <OpenGL/gl3.h>
#include <string>
#include "glm/glm.hpp"
#include "ResourceManager.h"
#include "SpriteBatch.h"

class Sprite {
public:
    Sprite() : m_textureName(""), m_dimensions(0.0f), m_angle(0), m_scale(1.0f) {}
    Sprite(std::string textureName, glm::vec4 dimensions) : m_textureName(textureName), m_dimensions(dimensions), m_angle(0), m_scale(1.0f) {}
    
    void render(SpriteBatch& spriteBatch);
    
    void setTextureName(std::string textureName) { m_textureName = textureName; }
    void setDimensions(glm::vec4 dimensions) { m_dimensions = dimensions; }
    void setAngle(int angle) { m_angle = angle; }
    void setScale(float scale) { m_scale = scale; }
    
    std::string getTextureName() { return m_textureName; }
    glm::vec4 getDimensions() { return m_dimensions; }
    int getAngle() { return m_angle; }
    float getScale() { return m_scale; }
    
private:
    std::string m_textureName;
    glm::vec4 m_dimensions;
    int m_angle;
    float m_scale;
};

#endif /* defined(__QuimiPop__Sprite__) */
