//
//  Vertex.h
//  GraphicsTutorial
//
//  Created by Eduardo Alberto Sanchez Alvarado & Graciela Garcia Diaz on 3/15/15.
//  Copyright (c) 2015 Eduardo Alberto Sanchez Alvarado & Graciela Garcia Diaz. All rights reserved.
//

#ifndef GraphicsTutorial_Vertex_h
#define GraphicsTutorial_Vertex_h

//#include <OpenGL/gl3.h>
#include <Windows.h>
#include <GL/glew.h>

struct Position {
    float x;
    float y;
};

struct ColorRGBA8 {
    ColorRGBA8() : r(0), g(0), b(0), a(0) {}
    ColorRGBA8(GLubyte R, GLubyte G, GLubyte B, GLubyte A) : r(R), g(G), b(B), a(A) {}
    GLubyte r;
    GLubyte g;
    GLubyte b;
    GLubyte a;
};

struct UV {
    float u;
    float v;
};

struct Vertex {
    Position position;
    ColorRGBA8 color;
    UV uv;
    
    void setPosition(float x, float y) {
        position.x = x;
        position.y = y;
    }
    
    void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a) {
        color = ColorRGBA8(r, g, b, a);
    };
    
    void setUV(float u, float v) {
        uv.u = u;
        uv.v = v;
    }
};

#endif
