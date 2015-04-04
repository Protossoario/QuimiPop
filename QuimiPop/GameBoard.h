//
//  GameBoard.h
//  QuimiPop
//
//  Created by Eduardo Alberto Sanchez Alvarado & Graciela Garcia Diaz on 3/22/15.
//  Copyright (c) 2015 Eduardo Alberto Sanchez Alvarado & Graciela Garcia Diaz. All rights reserved.
//

#ifndef __QuimiPop__GameBoard__
#define __QuimiPop__GameBoard__

#include <time.h>
#include <stdlib.h>
#include <string>

#include "glm/glm.hpp"
#include "SpriteBatch.h"
#include "Grid.h"

class GameBoard {
public:
    GameBoard(glm::vec2 position);
    
    void init();
    
    void update();
    void draw(SpriteBatch& spriteBatch);
    
    void setClickingDown(bool clickingDown);
    void updateMouseCoords(glm::vec2 mouseCoords);
    
private:
    constexpr const static float TILE_WIDTH = 75.0f;
    constexpr const static float TILE_HEIGHT = 75.0f;
    
    glm::vec4 getTileRectangle(int row, int col);
    glm::vec4 getHighlightedTileRectangle(int row, int col);
    int getRowForY(int y);
    int getColForX(int x);
    
    Grid m_boardGrid;
    
    glm::vec2 m_boardPosition;
    
    bool m_clickingDown;
    bool m_setMouseCoords;
    glm::vec2 m_originMouseCoords;
    glm::vec2 m_mouseCoords;
    
    bool m_highlighting;
    int m_highlightRow;
    int m_highlightCol;
};

#endif /* defined(__QuimiPop__GameBoard__) */
