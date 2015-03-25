//
//  ResourceManager.cpp
//  GraphicsTutorial
//
//  Created by Eduardo Alberto Sanchez Alvarado & Graciela Garcia Diaz on 3/17/15.
//  Copyright (c) 2015 Eduardo Alberto Sanchez Alvarado & Graciela Garcia Diaz. All rights reserved.
//

#include "ResourceManager.h"

TextureCache ResourceManager::_textureCache;

GLTexture ResourceManager::getTexture(std::string texturePath) {
    return _textureCache.getTexture(texturePath);
}