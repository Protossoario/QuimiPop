//
//  Sprite.h
//  GraphicsTutorial
//
//  Created by Eduardo Alberto Sanchez Alvarado & Graciela Garcia Diaz on 3/1/15.
//  Copyright (c) 2015 Eduardo Alberto Sanchez Alvarado & Graciela Garcia Diaz. All rights reserved.
//

#ifndef __GraphicsTutorial__Sprite__
#define __GraphicsTutorial__Sprite__

#include <OpenGL/gl3.h>
#include <stddef.h>
#include <string>
#include "Vertex.h"
#include "GLTexture.h"
#include "ResourceManager.h"

class Sprite {
public:
    Sprite();
    ~Sprite();
    void init(float x, float y, float width, float height, std::string texturePath);
    void draw();
    
private:
    int _x;
    int _y;
    int _width;
    int _height;
    GLuint _vboID;
    GLTexture _texture;
};

#endif /* defined(__GraphicsTutorial__Sprite__) */
