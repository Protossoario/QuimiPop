//
//  GridAnimator.h
//  QuimiPop
//
//  Created by Eduardo Alberto Sanchez Alvarado on 4/4/15.
//  Copyright (c) 2015 Eduardo Alberto Sanchez Alvarado. All rights reserved.
//

#ifndef __QuimiPop__GridAnimator__
#define __QuimiPop__GridAnimator__

#include <OpenGL/gl3.h>
#include <vector>
#include "SpriteBatch.h"

class GridAnimator {
public:
    void update();
    void render(SpriteBatch& spriteBatch);
};

#endif /* defined(__QuimiPop__GridAnimator__) */
