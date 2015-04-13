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
#include <vector>

#include "glm/glm.hpp"
#include "Sprite.h"
#include "SpriteBatch.h"
#include "Grid.h"

struct Tile {
    Tile(int Row, int Col) : row(Row), col(Col) {}
    int row;
    int col;
};

struct MoleculeAnimation {
    MoleculeAnimation() : currFrames(0), totalFrames(0), animating(false) {}
    std::vector<Tile> tiles;
    int currFrames;
    int totalFrames;
    bool animating;
};

class GameBoard : GridObserver {
public:
    GameBoard(glm::vec2 position);
    
    void init();
    
    void update();
    void draw(SpriteBatch& spriteBatch);
    
    void setClickingDown(bool clickingDown);
    void updateMouseCoords(glm::vec2 mouseCoords);
    
    bool isPointInsideBoard(glm::vec2 point);
    
    void formedMoleculeRow(int row, int col, int size);
    void formedMoleculeCol(int row, int col, int size);
    
private:
    constexpr const static float TILE_WIDTH = 75.0f;
    constexpr const static float TILE_HEIGHT = 75.0f;
    
    glm::vec4 getTileRectangle(int row, int col);
    glm::vec2 getTileForCoords(glm::vec2 coords);
    
    int getRowForY(int y);
    int getColForX(int x);
    
    void rescaleTile(Sprite* sprite, float scale);
    void updateColHighlight(bool highlight, int col);
    void updateRowHighlight(bool highlight, int row);
    void updateColOffset(int col, int offset);
    void updateRowOffset(int row, int offset);
    
    Grid m_boardGrid;
    std::vector<Sprite> m_sprites;
    Sprite* m_spriteGrid[8][8];
    
    MoleculeAnimation m_molAnimation;
    
    glm::vec2 m_boardPosition;
    
    bool m_clickingDown;
    bool m_setMouseCoords;
    glm::vec2 m_originMouseCoords;
    glm::vec2 m_currMouseCoords;
    
    bool m_highlighting;
    int m_highlightRow;
    int m_highlightCol;
};

#endif /* defined(__QuimiPop__GameBoard__) */
