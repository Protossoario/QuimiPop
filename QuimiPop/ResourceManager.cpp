//
//  ResourceManager.cpp
//  GraphicsTutorial
//
//  Created by Eduardo Alberto Sanchez Alvarado & Graciela Garcia Diaz on 3/17/15.
//  Copyright (c) 2015 Eduardo Alberto Sanchez Alvarado & Graciela Garcia Diaz. All rights reserved.
//

#include "ResourceManager.h"

TextureCache ResourceManager::m_textureCache;
ModelCache ResourceManager::m_modelCache;

GLTexture ResourceManager::getTexture(std::string texturePath) {
    return m_textureCache.getTexture(texturePath);
}

Mesh ResourceManager::getModel(std::string modelPath) {
	return m_modelCache.getModel(modelPath);
}