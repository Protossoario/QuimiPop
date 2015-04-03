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
    Glyph(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint Texture, float Depth, const Color& color);
    Glyph(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint Texture, float Depth, const Color& color, float angle);
    
    GLuint texture;
    float depth;
    
    Vertex topLeft;
    Vertex bottomLeft;
    Vertex topRight;
    Vertex bottomRight;
    
private:
    glm::vec2 rotatePoint(glm::vec2 point, float angle);
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
    void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const Color& color, float angle);
    
    void renderBatch();
    
private:
    void createRenderBatches();
    void createVertexArray();
    void sortGlyphs();
    
    static bool compareFrontToBack(Glyph* a, Glyph* b);
    static bool compareBackToFront(Glyph* a, Glyph* b);
    static bool compareTexture(Glyph* a, Glyph* b);
    
    GLuint m_vbo;
    GLuint m_vao;
    
    GlyphSortType m_sortType;
    
    std::vector<Glyph*> m_glyphPointers; // This is for sorting
    std::vector<Glyph> m_glyphs; // These are the actual glyphs
    std::vector<RenderBatch> m_renderBatches;
};

#endif /* defined(__GraphicsTutorial__SpriteBatch__) */
