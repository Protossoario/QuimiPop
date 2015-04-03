//
//  ParticleBatch2D.cpp
//  QuimiPop
//
//  Created by Eduardo Alberto Sanchez Alvarado on 4/3/15.
//  Copyright (c) 2015 Eduardo Alberto Sanchez Alvarado. All rights reserved.
//

#include "ParticleBatch2D.h"

void Particle2D::update() {
    m_position += m_velocity;
}

ParticleBatch2D::ParticleBatch2D() {}

ParticleBatch2D::~ParticleBatch2D() {
    delete [] m_particles;
}

void ParticleBatch2D::init(int maxParticles, float decayRate, GLTexture texture) {
    m_maxParticles = maxParticles;
    m_particles = new Particle2D[maxParticles];
    m_decayRate = decayRate;
    m_texture = texture;
}

void ParticleBatch2D::update() {
    for (int i = 0; i < m_maxParticles; i++) {
        if (m_particles[i].m_life > 0.0f) {
            m_particles[i].update();
            m_particles[i].m_life -= m_decayRate;
        }
    }
}

void ParticleBatch2D::draw(SpriteBatch* spriteBatch) {
    glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
    for (int i = 0; i < m_maxParticles; i++) {
        auto& particle = m_particles[i];
        if (particle.m_life > 0.0f) {
            glm::vec4 destRect(particle.m_position.x, particle.m_position.y, particle.m_width, particle.m_width);
            spriteBatch->draw(destRect, uvRect, m_texture.textureId, 0.0f, particle.m_color);
        }
    }
}

void ParticleBatch2D::addParticle(const glm::vec2 &position, const glm::vec2 &velocity, const Color &color, float width) {
    int particleIndex = findFreeParticle();
    
    auto& particle = m_particles[particleIndex];
    particle.m_life = 1.0f;
    particle.m_position = position;
    particle.m_velocity = velocity;
    particle.m_color = color;
    particle.m_width = width;
}

int ParticleBatch2D::findFreeParticle() {
    for (int i = m_lastFreeParticle; i < m_maxParticles; i++) {
        if (m_particles[i].m_life <= 0.0f) {
            m_lastFreeParticle = i;
            return i;
        }
    }
    
    for (int i = 0; i < m_lastFreeParticle; i++) {
        if (m_particles[i].m_life <= 0.0f) {
            m_lastFreeParticle = i;
            return i;
        }
    }
    
    // No particles are free in the buffer, so override first particle
    return 0;
}