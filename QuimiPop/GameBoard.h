//
//  GameBoard.h
//  QuimiPop
//
//  Created by Eduardo Alberto Sanchez Alvarado on 3/22/15.
//  Copyright (c) 2015 Eduardo Alberto Sanchez Alvarado. All rights reserved.
//

#ifndef __QuimiPop__GameBoard__
#define __QuimiPop__GameBoard__

#include <time.h>
#include <stdlib.h>
#include <string>

#include "glm/glm.hpp"
#include "ResourceManager.h"
#include "SpriteBatch.h"
#include "GLTexture.h"

class GameBoard {
public:
    GameBoard(glm::vec2 position);
    
    void init();
    
    void draw(SpriteBatch& spriteBatch);
    
private:
    glm::vec4 getTileRectangle(int row, int col);
    GLTexture getTileTexture(int row, int col);
    
    int _board[8][8];
    
    glm::vec2 _position;
};

#endif /* defined(__QuimiPop__GameBoard__) */
