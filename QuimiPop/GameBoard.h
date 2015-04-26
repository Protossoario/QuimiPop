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
#include <map>

#include "glm/glm.hpp"
#include "Sprite.h"
#include "SpriteBatch.h"
#include "Grid.h"
#include "AudioEngine.h"

struct Tile {
    Tile(int Row, int Col) : row(Row), col(Col) {}
    int row;
    int col;
};

class AnimationObserver {
public:
    virtual void notifyAnimationFinished() = 0;
};

class MoleculeAnimation {
public:
    MoleculeAnimation() : m_currFrames(0), m_totalFrames(0), m_animating(false) {}
    
    void start(int frames);
    void addTile(int row, int col);
    void update(std::map<int, Sprite>& spriteMap);
    
    bool isAnimating() { return m_animating; }
    void registerObserver(AnimationObserver* obs) { m_observer = obs; }
    
private:
    std::vector<Tile> m_tiles;
    AnimationObserver* m_observer;
    int m_currFrames;
    int m_totalFrames;
    bool m_animating;
};

class GameBoard : GridObserver, AnimationObserver {
public:
    GameBoard(glm::vec2 position);
	GameBoard(glm::vec2 position, SoundEffect moleculeSound);
    
    void init();
    
    void update();
    void draw(SpriteBatch& spriteBatch);
    
    void setClickingDown(bool clickingDown);
    void updateMouseCoords(glm::vec2 mouseCoords);
	Molecule getHoverMolecule();
	void resetHoverMolecule();
	int getScore();
	void resetScore();
	int getRemainingTurns();
	void resetRemainingTurns();

	void setMoleculeSound(SoundEffect moleculeSound);
    
    bool isPointInsideBoard(glm::vec2 point);
    
    void formedMoleculeRow(int row, int col, int size);
    void formedMoleculeCol(int row, int col, int size);
    
    void notifyAnimationFinished();
    
private:
    glm::vec4 getTileRectangle(int row, int col);
    glm::vec2 getTileForCoords(glm::vec2 coords);
    
    int getRowForY(int y);
    int getColForX(int x);
    
    void rescaleTile(Tile tile, float scale);
    void updateColHighlight(bool highlight, int col);
    void updateRowHighlight(bool highlight, int row);
    void updateColOffset(int col, int offset);
    void updateRowOffset(int row, int offset);
    
    void refreshSpritesFromGrid();
    void refreshRowFromGrid(int row);
    void refreshColFromGrid(int col);
    
    Grid m_boardGrid;
    std::map<int, Sprite> m_spriteMap;
    
    MoleculeAnimation m_molAnimation;

	Molecule m_hoverMolecule = NONE;

	SoundEffect m_moleculeSound;
    
    glm::vec2 m_boardPosition;
    
    bool m_clickingDown;
    bool m_setMouseCoords;
    glm::vec2 m_originMouseCoords;
    glm::vec2 m_currMouseCoords;
    glm::vec2 m_offset;
    
    bool m_highlighting;
    int m_highlightRow;
    int m_highlightCol;

	int m_score = 0;
	int m_remainingTurns = 15;
};

#endif /* defined(__QuimiPop__GameBoard__) */
