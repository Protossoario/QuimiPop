//
//  GameBoard.cpp
//  QuimiPop
//
//  Created by Eduardo Alberto Sanchez Alvarado & Graciela Garcia Diaz on 3/22/15.
//  Copyright (c) 2015 Eduardo Alberto Sanchez Alvarado & Graciela Garcia Diaz. All rights reserved.
//

#include "GameBoard.h"

GameBoard::GameBoard(glm::vec2 position) : m_boardPosition(position), m_clickingDown(false), m_setMouseCoords(false), m_highlighting(false), m_highlightCol(-1), m_highlightRow(-1) {}

void GameBoard::init() {
    srand(time(NULL));
    
    m_boardGrid.init();
}

void GameBoard::update() {
    if (m_clickingDown && !m_setMouseCoords && !m_highlighting) {
        glm::vec2 mouseOffset = m_mouseCoords - m_originMouseCoords;
        if (abs(mouseOffset.x) > abs(mouseOffset.y) && abs(mouseOffset.x) > TILE_WIDTH / 4) {
            m_highlightRow = getRowForY(m_mouseCoords.y);
            m_highlighting = true;
            printf("Highlighted row: %d\n", m_highlightRow);
        }
        else if (abs(mouseOffset.x) < abs(mouseOffset.y) && abs(mouseOffset.y) > TILE_HEIGHT / 4) {
            m_highlightCol = getColForX(m_mouseCoords.x);
            m_highlighting = true;
            printf("Highlighted col: %d\n", m_highlightCol);
        }
    }
}

void GameBoard::draw(SpriteBatch &spriteBatch) {
    glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
    Color color;
    color.r = 255;
    color.g = 255;
    color.b = 255;
    color.a = 255;
    
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            glm::vec4 destRect;
            if (row == m_highlightRow || col == m_highlightCol) {
                destRect = getHighlightedTileRectangle(row, col);
            }
            else {
                destRect = getTileRectangle(row, col);
            }
            GLTexture texture = m_boardGrid.getTileTexture(row, col);
            spriteBatch.draw(destRect, uv, texture.textureId, 0.0f, color);
        }
    }
}

void GameBoard::setClickingDown(bool clickingDown) {
    if (clickingDown && !m_clickingDown) {
        m_setMouseCoords = true;
    }
    else {
        m_setMouseCoords = false;
    }
    m_clickingDown = clickingDown;
    if (!m_clickingDown && m_highlighting) {
        glm::vec2 offset = m_mouseCoords - m_originMouseCoords;
        if (m_highlightRow > -1) {
            int rowOffset = (offset.x > 0 ? offset.x + TILE_WIDTH / 2 : offset.x - TILE_WIDTH / 2) / TILE_WIDTH;
            m_boardGrid.moveGrid(1, m_highlightRow, rowOffset);
            m_boardGrid.checkGrid(1, m_highlightRow);
        }
        else if (m_highlightCol > -1) {
            int colOffset = (offset.y > 0 ? offset.y + TILE_HEIGHT / 2 : offset.y - TILE_HEIGHT / 2) / TILE_HEIGHT;
            m_boardGrid.moveGrid(0, m_highlightCol, colOffset);
            m_boardGrid.checkGrid(0, m_highlightCol);
        }
        m_highlighting = false;
        m_highlightRow = -1;
        m_highlightCol = -1;
    }
}

void GameBoard::updateMouseCoords(glm::vec2 mouseCoords) {
    if (m_setMouseCoords) {
        m_originMouseCoords = mouseCoords;
    }
    else {
        m_mouseCoords = mouseCoords;
    }
}

bool GameBoard::isPointInsideBoard(glm::vec2 point) {
    return point.x >= m_boardPosition.x && point.x <= m_boardPosition.x + TILE_WIDTH * 8 && point.y >= m_boardPosition.y && point.y <= m_boardPosition.y + TILE_HEIGHT * 8;
}

glm::vec4 GameBoard::getTileRectangle(int row, int col) {
    return glm::vec4(
        TILE_WIDTH * col + m_boardPosition.x,
        TILE_HEIGHT * row + m_boardPosition.y,
        TILE_WIDTH,
        TILE_HEIGHT
    );
}

glm::vec4 GameBoard::getHighlightedTileRectangle(int row, int col) {
    glm::vec2 mouseOffset = m_mouseCoords - m_originMouseCoords;
    int gridWidth = TILE_WIDTH * 8;
    int gridHeight = TILE_HEIGHT * 8;
    float x, y, width, height;
    
    const static float HIGHLIGHT_SCALE = 1.25;
    
    width = TILE_WIDTH * HIGHLIGHT_SCALE;
    height = TILE_HEIGHT * HIGHLIGHT_SCALE;
        
    if (m_highlightRow > -1) {
        int offset = (mouseOffset.x > 0 ? mouseOffset.x + TILE_WIDTH / 2 : mouseOffset.x - TILE_WIDTH / 2) / TILE_WIDTH;
        col = (col + offset + 8) % 8;
    }
    else if (m_highlightCol > -1) {
        int offset = (mouseOffset.y > 0 ? mouseOffset.y + TILE_HEIGHT / 2 : mouseOffset.y - TILE_HEIGHT / 2) / TILE_HEIGHT;
        row = (row + offset + 8) % 8;
    }
    
    x = TILE_WIDTH * col - TILE_WIDTH * (HIGHLIGHT_SCALE - 1) / 2 + m_boardPosition.x;
    y = TILE_HEIGHT * row - TILE_HEIGHT * (HIGHLIGHT_SCALE - 1) / 2 + m_boardPosition.y;
    
    return glm::vec4(
        x,
        y,
        width,
        height
    );
}

int GameBoard::getRowForY(int y) {
    return (y - m_boardPosition.y) / TILE_HEIGHT;
}

int GameBoard::getColForX(int x) {
    return (x - m_boardPosition.x) / TILE_WIDTH;
}