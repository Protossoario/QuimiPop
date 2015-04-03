//
//  ParticleEngine2D.h
//  QuimiPop
//
//  Created by Eduardo Alberto Sanchez Alvarado on 4/3/15.
//  Copyright (c) 2015 Eduardo Alberto Sanchez Alvarado. All rights reserved.
//

#ifndef __QuimiPop__ParticleEngine2D__
#define __QuimiPop__ParticleEngine2D__

#include "ParticleBatch2D.h"
#include "SpriteBatch.h"

class ParticleEngine2D {
public:
    ParticleEngine2D();
    ~ParticleEngine2D();
    
    void addParticleBatch(ParticleBatch2D* particleBatch);
    void update();
    void draw(SpriteBatch* spriteBatch);
    
private:
    std::vector<ParticleBatch2D*> m_batches;
};

#endif /* defined(__QuimiPop__ParticleEngine2D__) */
