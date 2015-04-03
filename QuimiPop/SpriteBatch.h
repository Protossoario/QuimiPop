//
//  SpriteBatch.h
//  GraphicsTutorial
//
//  Created by Eduardo Alberto Sanchez Alvarado & Graciela Garcia Diaz on 3/21/15.
//  Copyright (c) 2015 Eduardo Alberto Sanchez Alvarado & Graciela Garcia Diaz. All rights reserved.
//

#ifndef __GraphicsTutorial__SpriteBatch__
#define __GraphicsTutorial__SpriteBatch__

#include <OpenGL/gl3.h>
#include "glm/glm.hpp"
#include <vector>
#include <algorithm>
#include "Vertex.h"

enum class GlyphSortType {
    NONE,
    FRONT_TO_BACK,
    BACK_TO_FRONT,
    TEXTURE
};

class Glyph {
public:
    Glyph();
    Glyph(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const Color& color) : _texture(texture), _depth(depth) {
        _topLeft.color = color;
        _topLeft.setPosition(destRect.x, destRect.y + destRect.w);
        _topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);
        
        _bottomLeft.color = color;
        _bottomLeft.setPosition(destRect.x, destRect.y);
        _bottomLeft.setUV(uvRect.x, uvRect.y);
        
        _bottomRight.color = color;
        _bottomRight.setPosition(destRect.x + destRect.z, destRect.y);
        _bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);
        
        _topRight.color = color;
        _topRight.setPosition(destRect.x + destRect.z, destRect.y + destRect.w);
        _topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);
    }
    
    GLuint _texture;
    float _depth;
    
    Vertex _topLeft;
    Vertex _bottomLeft;
    Vertex _topRight;
    Vertex _bottomRight;
};

class RenderBatch {
public:
    RenderBatch(GLuint Offset, GLuint NumVertices, GLuint Texture) : offset(Offset), numVertices(NumVertices), texture(Texture) {}
    
    GLuint offset;
    GLuint numVertices;
    GLuint texture;
};

class SpriteBatch {
public:
    SpriteBatch();
    
    void init();
    
    void begin(GlyphSortType sortType = GlyphSortType::TEXTURE);
    void end();
    
    void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const Color& color);
    
    void renderBatch();
    
private:
    void createRenderBatches();
    void createVertexArray();
    void sortGlyphs();
    
    static bool compareFrontToBack(Glyph* a, Glyph* b);
    static bool compareBackToFront(Glyph* a, Glyph* b);
    static bool compareTexture(Glyph* a, Glyph* b);
    
    GLuint _vbo;
    GLuint _vao;
    
    GlyphSortType _sortType;
    
    std::vector<Glyph*> _glyphPointers; // This is for sorting
    std::vector<Glyph> _glyphs; // These are the actual glyphs
    std::vector<RenderBatch> _renderBatches;
};

#endif /* defined(__GraphicsTutorial__SpriteBatch__) */
