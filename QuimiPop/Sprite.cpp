//
//  Sprite.cpp
//  QuimiPop
//
//  Created by Eduardo Alberto Sanchez Alvarado on 4/4/15.
//  Copyright (c) 2015 Eduardo Alberto Sanchez Alvarado. All rights reserved.
//

#include "Sprite.h"

void Sprite::render(SpriteBatch &spriteBatch) {
    const static glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
    Color color;
    color.r = 255;
    color.g = 255;
    color.b = 255;
    color.a = 255;
    glm::vec4 destRect(
                       m_dimensions.x - m_dimensions.z * (m_scale - 1),
                       m_dimensions.y - m_dimensions.w * (m_scale - 1),
                       m_dimensions.z * m_scale,
                       m_dimensions.w * m_scale);
    if (m_angle == 0) {
        spriteBatch.draw(destRect, uvRect, ResourceManager::getTexture(m_textureName).textureId, 0, color);
    }
    else {
        spriteBatch.draw(destRect, uvRect, ResourceManager::getTexture(m_textureName).textureId, 0, color, m_angle);
    }
}