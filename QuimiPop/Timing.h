//
//  Timing.h
//  GraphicsTutorial
//
//  Created by Eduardo Alberto Sanchez Alvarado & Graciela Garcia Diaz on 3/21/15.
//  Copyright (c) 2015 Eduardo Alberto Sanchez Alvarado & Graciela Garcia Diaz. All rights reserved.
//

#ifndef GraphicsTutorial_Timing_h
#define GraphicsTutorial_Timing_h

#include <SDL2/SDL.h>

class FPSLimiter {
public:
    void init(float maxFPS);
    
    void setMaxFPS(float maxFPS);
    
    void begin();
    // end will return the current FPS
    float end();
    
private:
    void calculateFPS();
    
    float m_fps;
    float m_maxFPS;
    float m_frameTime;
    unsigned int m_startTicks;
};

#endif
