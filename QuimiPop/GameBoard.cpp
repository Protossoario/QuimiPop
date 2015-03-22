//
//  GameBoard.cpp
//  QuimiPop
//
//  Created by Eduardo Alberto Sanchez Alvarado on 3/22/15.
//  Copyright (c) 2015 Eduardo Alberto Sanchez Alvarado. All rights reserved.
//

#include "GameBoard.h"

GameBoard::GameBoard(glm::vec2 position) : _position(position) {}

void GameBoard::init() {
    srand(time(NULL));
    
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            _board[row][col] = (rand() % 8);
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
    
    glm::vec4 rectangle(_position.x, _position.y, 30.0f, 30.0f);
    
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            glm::vec4 destRect = getTileRectangle(row, col);
            GLTexture texture = getTileTexture(row, col);
            spriteBatch.draw(destRect, uv, texture.textureId, 0.0f, color);
        }
    }
}

glm::vec4 GameBoard::getTileRectangle(int row, int col) {
    const static float TILE_WIDTH = 50.0f;
    const static float TILE_HEIGHT = 50.0f;
    
    return glm::vec4(TILE_WIDTH * row + TILE_WIDTH / 2 + _position.x, TILE_HEIGHT * col + TILE_HEIGHT / 2 + _position.y, TILE_WIDTH, TILE_HEIGHT);
}

GLTexture GameBoard::getTileTexture(int row, int col) {
    std::string filePath = "/Users/EduardoS/Documents/Programacion/XCode Projects/QuimiPop/QuimiPop/Textures/";
    switch (_board[row][col]) {
        case 0:
            filePath += "blue_gem.png";
            break;
            
        case 1:
            filePath += "gray_gem.png";
            break;
            
        case 2:
            filePath += "light_blue_gem.png";
            break;
            
        case 3:
            filePath += "orange_gem.png";
            break;
            
        case 4:
            filePath += "purple_gem.png";
            break;
            
        case 5:
            filePath += "red_gem.png";
            break;
            
        case 6:
            filePath += "teal_gem.png";
            break;
            
        case 7:
            filePath += "yellow_gem.png";
            break;
            
        default:
            filePath += "blue_gem.png";
            break;
    }
    return ResourceManager::getTexture(filePath);
}