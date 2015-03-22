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
    
    void setClickingDown(bool clickingDown);
    void updateMouseCoords(glm::vec2 mouseCoords);
    
private:
    constexpr const static float TILE_WIDTH = 75.0f;
    constexpr const static float TILE_HEIGHT = 75.0f;
    
    void scrollColumn(int column, int offset);
    void scrollRow(int row, int offset);
    
    glm::vec4 getTileRectangle(int row, int col);
    GLTexture getTileTexture(int row, int col);
    int getRowForY(int y);
    int getColForX(int x);
    
    int _board[8][8];
    
    glm::vec2 _position;
    
    bool _clickingDown;
    bool _setMouseCoords;
    glm::vec2 _originMouseCoords;
    glm::vec2 _mouseCoords;
    
    bool _highlighting;
    int _highlightRow;
    int _highlightCol;
};

#endif /* defined(__QuimiPop__GameBoard__) */
