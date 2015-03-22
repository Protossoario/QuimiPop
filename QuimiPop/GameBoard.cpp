//
//  GameBoard.cpp
//  QuimiPop
//
//  Created by Eduardo Alberto Sanchez Alvarado on 3/22/15.
//  Copyright (c) 2015 Eduardo Alberto Sanchez Alvarado. All rights reserved.
//

#include "GameBoard.h"

/* PUBLIC METHODS */

GameBoard::GameBoard(glm::vec2 position) : _position(position), _clickingDown(false), _setMouseCoords(false), _highlighting(false), _highlightCol(-1), _highlightRow(-1) {}

void GameBoard::init() {
    srand(time(NULL));
    
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            _board[row][col] = (rand() % 11);
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
    
    if (_clickingDown && !_setMouseCoords && !_highlighting) {
        glm::vec2 mouseOffset = _mouseCoords - _originMouseCoords;
        if (abs(mouseOffset.x) > abs(mouseOffset.y) && abs(mouseOffset.x) > TILE_WIDTH / 4) {
            _highlightRow = getRowForY(_mouseCoords.y);
            _highlighting = true;
            printf("Highlighted row: %d\n", _highlightRow);
        }
        else if (abs(mouseOffset.x) < abs(mouseOffset.y) && abs(mouseOffset.y) > TILE_HEIGHT / 4) {
            _highlightCol = getColForX(_mouseCoords.x);
            _highlighting = true;
            printf("Highlighted col: %d\n", _highlightCol);
        }
    }
    
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            glm::vec4 destRect = getTileRectangle(row, col);
            GLTexture texture = getTileTexture(row, col);
            spriteBatch.draw(destRect, uv, texture.textureId, 0.0f, color);
        }
    }
}

void GameBoard::setClickingDown(bool clickingDown) {
    if (clickingDown && !_clickingDown) {
        _setMouseCoords = true;
    }
    else {
        _setMouseCoords = false;
    }
    _clickingDown = clickingDown;
    if (!_clickingDown && _highlighting) {
        glm::vec2 offset = _originMouseCoords - _mouseCoords;
        if (_highlightRow > -1) {
            int rowOffset = offset.x / TILE_WIDTH;
            scrollRow(_highlightRow, rowOffset);
        }
        else if (_highlightCol > -1) {
            int colOffset = offset.y / TILE_HEIGHT;
            scrollColumn(_highlightCol, colOffset);
        }
        _highlighting = false;
        _highlightRow = -1;
        _highlightCol = -1;
    }
}

void GameBoard::updateMouseCoords(glm::vec2 mouseCoords) {
    if (_setMouseCoords) {
        _originMouseCoords = mouseCoords;
    }
    else {
        _mouseCoords = mouseCoords;
    }
}

/* PRIVATE METHODS */

void GameBoard::scrollColumn(int column, int offset) {
    if (offset == 0) {
        return;
    }
    int temp[8];
    for (int i = 0; i < 8; i++) {
        temp[i] = _board[i][column];
    }
    for (int i = 0; i < 8; i++) {
        _board[i][column] = temp[(i + offset + 8) % 8];
    }
}

void GameBoard::scrollRow(int row, int offset) {
    if (offset == 0) {
        return;
    }
    int temp[8];
    for (int i = 0; i < 8; i++) {
        temp[i] = _board[row][i];
    }
    for (int i = 0; i < 8; i++) {
        _board[row][i] = temp[(i + offset + 8) % 8];
    }
}

glm::vec4 GameBoard::getTileRectangle(int row, int col) {
    if (row == _highlightRow) {
        glm::vec2 offset = _mouseCoords - _originMouseCoords;
        return glm::vec4((int)(offset.x + TILE_WIDTH * col + 8 * TILE_WIDTH) % (int)(8 * TILE_WIDTH) + _position.x, TILE_HEIGHT * row + _position.y, TILE_WIDTH * 1.25, TILE_HEIGHT * 1.25);
    }
    else if (col == _highlightCol) {
        glm::vec2 offset = _mouseCoords - _originMouseCoords;
        return glm::vec4(TILE_WIDTH * col + _position.x, (int)(offset.y + TILE_HEIGHT * row + 8 * TILE_HEIGHT) % (int)(8 * TILE_HEIGHT) + _position.y, TILE_WIDTH * 1.25, TILE_HEIGHT * 1.25);
    }
    return glm::vec4(TILE_WIDTH * col + _position.x, TILE_HEIGHT * row + _position.y, TILE_WIDTH, TILE_HEIGHT);
}

GLTexture GameBoard::getTileTexture(int row, int col) {
    std::string filePath = "/Users/EduardoS/Documents/Programacion/XCode Projects/QuimiPop/QuimiPop/Textures/";
    switch (_board[row][col]) {
        case 0:
            filePath += "Acido.png";
            break;
            
        case 1:
            filePath += "Agua.png";
            break;
            
        case 2:
            filePath += "Azucar.png";
            break;
            
        case 3:
            filePath += "Azufre.png";
            break;
            
        case 4:
            filePath += "Carbon dioxide.png";
            break;
            
        case 5:
            filePath += "Carbon.png";
            break;
            
        case 6:
            filePath += "Hydrogen.png";
            break;
            
        case 7:
            filePath += "Kriptonita.png";
            break;
        
        case 8:
            filePath += "Methane.png";
            break;
            
        case 9:
            filePath += "Nitrogen.png";
            break;
            
        case 10:
            filePath += "Oxygen.png";
            break;
            
        default:
            filePath += "Kriptonita.png";
            break;
    }
    return ResourceManager::getTexture(filePath);
}

int GameBoard::getRowForY(int y) {
    return (y - _position.y) / TILE_HEIGHT;
}

int GameBoard::getColForX(int x) {
    return (x - _position.x) / TILE_WIDTH;
}