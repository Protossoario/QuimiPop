//
//  ResourceManager.h
//  GraphicsTutorial
//
//  Created by Eduardo Alberto Sanchez Alvarado & Graciela Garcia Diaz on 3/17/15.
//  Copyright (c) 2015 Eduardo Alberto Sanchez Alvarado & Graciela Garcia Diaz. All rights reserved.
//

#ifndef __GraphicsTutorial__ResourceManager__
#define __GraphicsTutorial__ResourceManager__

#include "TextureCache.h"
#include "ModelCache.h"
#include <string>

class ResourceManager {
public:
    static GLTexture getTexture(std::string texturePath);
	static Mesh getModel(std::string modelPath);
    
private:
    static TextureCache m_textureCache;
	static ModelCache m_modelCache;
};

#endif /* defined(__GraphicsTutorial__ResourceManager__) */
