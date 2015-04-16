//
//  GLTexture.h
//  GraphicsTutorial
//
//  Created by Eduardo Alberto Sanchez Alvarado & Graciela Garcia Diaz on 3/16/15.
//  Copyright (c) 2015 Eduardo Alberto Sanchez Alvarado & Graciela Garcia Diaz. All rights reserved.
//

#ifndef GraphicsTutorial_GLTexture_h
#define GraphicsTutorial_GLTexture_h

//#include <OpenGL/gl3.h>
#include <Windows.h>
#include <GL/glew.h>

struct GLTexture {
    GLuint textureId;
    int width;
    int height;
};

#endif
