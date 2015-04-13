//
//  GameBoard.cpp
//  QuimiPop
//
//  Created by Eduardo Alberto Sanchez Alvarado & Graciela Garcia Diaz on 3/22/15.
//  Copyright (c) 2015 Eduardo Alberto Sanchez Alvarado & Graciela Garcia Diaz. All rights reserved.
//

#include "GameBoard.h"

void GameBoard::formedMoleculeRow(int row, int col, int size) {
    printf("Formed molecule on a row! Row: %d, Col %d, Size %d\n", row, col, size);
}

void GameBoard::formedMoleculeCol(int row, int col, int size) {
    printf("Formed molecule on a column! Row: %d, Col %d, Size %d\n", row, col, size);
    m_molAnimation.animating = true;
    m_molAnimation.currFrames = 0;
    m_molAnimation.totalFrames = 90;
    for (int i = row; i < row + size; i++) {
        m_molAnimation.tiles.emplace_back(i, col);
    }
}

GameBoard::GameBoard(glm::vec2 position) : m_boardPosition(position), m_clickingDown(false), m_setMouseCoords(false), m_highlighting(false), m_highlightCol(-1), m_highlightRow(-1) {}

void GameBoard::init() {
    srand(time(NULL));
    
    m_boardGrid.init();
    m_boardGrid.setGridObserver((GridObserver*)this);
    
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            m_sprites.emplace_back(m_boardGrid.getTileTexturePath(row, col), getTileRectangle(row, col));
            m_spriteGrid[row][col] = &m_sprites.back();
        }
    }
}

void GameBoard::update() {
    if (m_clickingDown && !m_setMouseCoords) {
        glm::vec2 baseTile = getTileForCoords(m_originMouseCoords);
        glm::vec2 offsetTile = getTileForCoords(m_currMouseCoords);
        glm::vec2 offset = offsetTile - baseTile;
        if (!m_highlighting && (std::abs((int)offset.x) > 0 || std::abs((int)offset.y) > 0)) {
            if (std::abs(offset.x) > std::abs(offset.y)) {
                m_highlightRow = (int)baseTile.y;
                updateRowHighlight(true, m_highlightRow);
                printf("Highlighted row: %d\n", m_highlightRow);
            }
            else {
                m_highlightCol = (int)baseTile.x;
                updateColHighlight(true, m_highlightCol);
                printf("Highlighted col: %d\n", m_highlightCol);
            }
            m_highlighting = true;
        }
        if (m_highlightRow != -1) {
            updateRowOffset(m_highlightRow, (int)offset.x);
        }
        else if (m_highlightCol != -1) {
            updateColOffset(m_highlightCol, (int)offset.y);
        }
    }
    
    if (m_molAnimation.animating) {
        float angle = 6.2832f * (float)m_molAnimation.currFrames / (float)m_molAnimation.totalFrames;
        printf("Angle: %.1f\n", angle);
        for (auto& tile : m_molAnimation.tiles) {
            m_spriteGrid[tile.row][tile.col]->rotation = angle;
        }
        m_molAnimation.currFrames++;
        if (m_molAnimation.currFrames == m_molAnimation.totalFrames) {
            m_sprites.clear();
            for (int row = 0; row < 8; row++) {
                for (int col = 0; col < 8; col++) {
                    m_sprites.emplace_back(m_boardGrid.getTileTexturePath(row, col), getTileRectangle(row, col));
                    m_spriteGrid[row][col] = &m_sprites.back();
                }
            }
            m_molAnimation.animating = false;
            m_molAnimation.tiles.clear();
        }
    }
}

void GameBoard::draw(SpriteBatch &spriteBatch) {
    static glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
    
    for (auto& sprite : m_sprites) {
        spriteBatch.draw(sprite.rectangle, uv, (ResourceManager::getTexture(sprite.texturePath)).textureId, 0.0f, sprite.color, sprite.rotation);
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
        glm::vec2 offset = m_currMouseCoords - m_originMouseCoords;
        if (m_highlightRow > -1) {
            int rowOffset = (offset.x > 0 ? offset.x + TILE_WIDTH / 2 : offset.x - TILE_WIDTH / 2) / TILE_WIDTH;
            m_boardGrid.moveGrid(1, m_highlightRow, rowOffset);
            m_boardGrid.checkGrid(1, m_highlightRow);
            updateRowHighlight(false, m_highlightRow);
        }
        else if (m_highlightCol > -1) {
            int colOffset = (offset.y > 0 ? offset.y + TILE_HEIGHT / 2 : offset.y - TILE_HEIGHT / 2) / TILE_HEIGHT;
            m_boardGrid.moveGrid(0, m_highlightCol, colOffset);
            m_boardGrid.checkGrid(0, m_highlightCol);
            updateColHighlight(false, m_highlightCol);
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
        m_currMouseCoords = mouseCoords;
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

glm::vec2 GameBoard::getTileForCoords(glm::vec2 coords) {
    return glm::vec2((coords.x - m_boardPosition.x) / TILE_WIDTH, (coords.y - m_boardPosition.y) / TILE_HEIGHT);
}

int GameBoard::getRowForY(int y) {
    return (y - m_boardPosition.y) / TILE_HEIGHT;
}

int GameBoard::getColForX(int x) {
    return (x - m_boardPosition.x) / TILE_WIDTH;
}

void GameBoard::rescaleTile(Sprite *sprite, float scale) {
    float oldWidth = sprite->rectangle.z;
    sprite->rectangle.z = scale * TILE_WIDTH;
    sprite->rectangle.x = sprite->rectangle.x - (sprite->rectangle.z - oldWidth) / 2;
    
    float oldHeight = sprite->rectangle.w;
    sprite->rectangle.w = scale * TILE_HEIGHT;
    sprite->rectangle.y = sprite->rectangle.y - (sprite->rectangle.w - oldHeight) / 2;
}

void GameBoard::updateColHighlight(bool highlight, int col) {
    for (int row = 0; row < 8; row++) {
        if (highlight) {
            rescaleTile(m_spriteGrid[row][col], 1.25);
        }
        else {
            rescaleTile(m_spriteGrid[row][col], 1);
        }
    }
}

void GameBoard::updateRowHighlight(bool highlight, int row) {
    for (int col = 0; col < 8; col++) {
        if (highlight) {
            rescaleTile(m_spriteGrid[row][col], 1.25);
        }
        else {
            rescaleTile(m_spriteGrid[row][col], 1);
        }
    }
}

void GameBoard::updateColOffset(int col, int offset) {
    for (int row = 0; row < 8; row++) {
        m_spriteGrid[row][col]->rectangle.y = TILE_HEIGHT * ((row + offset + 8) % 8) + m_boardPosition.y - TILE_HEIGHT / 8;
    }
}

void GameBoard::updateRowOffset(int row, int offset) {
    for (int col = 0; col < 8; col++) {
        m_spriteGrid[row][col]->rectangle.x = TILE_WIDTH * ((col + offset + 8) % 8) + m_boardPosition.x - TILE_WIDTH / 8;
    }
}