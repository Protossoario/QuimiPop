//
//  ParticleEngine2D.cpp
//  QuimiPop
//
//  Created by Eduardo Alberto Sanchez Alvarado on 4/3/15.
//  Copyright (c) 2015 Eduardo Alberto Sanchez Alvarado. All rights reserved.
//

#include "ParticleEngine2D.h"

ParticleEngine2D::ParticleEngine2D() {}

ParticleEngine2D::~ParticleEngine2D() {}

void ParticleEngine2D::addParticleBatch(ParticleBatch2D *particleBatch) {
    m_batches.push_back(particleBatch);
}

void ParticleEngine2D::update() {
    for (auto& batch : m_batches) {
        batch->update();
    }
}

void ParticleEngine2D::draw(SpriteBatch *spriteBatch) {
    for (auto& batch : m_batches) {
        spriteBatch->begin();
        batch->draw(spriteBatch);
        spriteBatch->end();
        
        spriteBatch->renderBatch();
    }
}