//
//  ParticleBatch2D.h
//  QuimiPop
//
//  Created by Eduardo Alberto Sanchez Alvarado on 4/3/15.
//  Copyright (c) 2015 Eduardo Alberto Sanchez Alvarado. All rights reserved.
//

#ifndef __QuimiPop__ParticleBatch2D__
#define __QuimiPop__ParticleBatch2D__

#include "glm/glm.hpp"
#include "Vertex.h"
#include "SpriteBatch.h"
#include "GLTexture.h"

class Particle2D {
public:
    friend class ParticleBatch2D;
    void update();
    
private:
    glm::vec2 m_position = glm::vec2(0.0f);
    glm::vec2 m_velocity = glm::vec2(0.0f);
    ColorRGBA8 m_color;
    float m_life = 1.0f;
    bool m_isActive = false;
    float m_width = 0.0f;
};

class ParticleBatch2D {
public:
    ParticleBatch2D();
    ~ParticleBatch2D();
    
    void init(int maxParticles, float decayRate, GLTexture texture);
    void update();
    void draw(SpriteBatch* spriteBatch);
    void addParticle(const glm::vec2& position, const glm::vec2& velocity, const ColorRGBA8& color, float width);
    
private:
    int findFreeParticle();
    
    float m_decayRate = 0.1f;
    Particle2D* m_particles = nullptr;
    int m_maxParticles = 0;
    int m_lastFreeParticle = 0;
    GLTexture m_texture;
};

#endif /* defined(__QuimiPop__ParticleBatch2D__) */
