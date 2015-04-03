//
//  GameBoard.cpp
//  QuimiPop
//
//  Created by Eduardo Alberto Sanchez Alvarado & Graciela Garcia Diaz on 3/22/15.
//  Copyright (c) 2015 Eduardo Alberto Sanchez Alvarado & Graciela Garcia Diaz. All rights reserved.
//

#include "GameBoard.h"

GameBoard::GameBoard(glm::vec2 position) : m_position(position), m_clickingDown(false), m_setMouseCoords(false), m_highlighting(false), m_highlightCol(-1), m_highlightRow(-1) {}

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
        }
        else if (abs(mouseOffset.x) < abs(mouseOffset.y) && abs(mouseOffset.y) > TILE_HEIGHT / 4) {
            m_highlightCol = getColForX(m_mouseCoords.x);
            m_highlighting = true;
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
            glm::vec4 destRect = getTileRectangle(row, col);
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

glm::vec4 GameBoard::getTileRectangle(int row, int col) {
    if (row == m_highlightRow) {
        glm::vec2 mouseOffset = m_mouseCoords - m_originMouseCoords;
        int squareWidth = TILE_WIDTH * 8;
        return glm::vec4((int)(mouseOffset.x + TILE_WIDTH * col + squareWidth) % squareWidth + m_position.x, TILE_HEIGHT * row + m_position.y, TILE_WIDTH * 1.25, TILE_HEIGHT * 1.25);
    }
    else if (col == m_highlightCol) {
        glm::vec2 mouseOffset = m_mouseCoords - m_originMouseCoords;
        int squareHeight = TILE_HEIGHT * 8;
        return glm::vec4(TILE_WIDTH * col + m_position.x, (int)(mouseOffset.y + TILE_HEIGHT * row + squareHeight) % squareHeight + m_position.y, TILE_WIDTH * 1.25, TILE_HEIGHT * 1.25);
    }
    return glm::vec4(TILE_WIDTH * col + m_position.x, TILE_HEIGHT * row + m_position.y, TILE_WIDTH, TILE_HEIGHT);
}

int GameBoard::getRowForY(int y) {
    return (y - m_position.y) / TILE_HEIGHT;
}

int GameBoard::getColForX(int x) {
    return (x - m_position.x) / TILE_WIDTH;
}