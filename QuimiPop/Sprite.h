//
//  Sprite.h
//  QuimiPop
//
//  Created by Eduardo Alberto Sanchez Alvarado on 4/10/15.
//  Copyright (c) 2015 Eduardo Alberto Sanchez Alvarado. All rights reserved.
//

#ifndef QuimiPop_Sprite_h
#define QuimiPop_Sprite_h

#include <string>
#include "glm/glm.hpp"

#include "Vertex.h"

struct Sprite {
    Sprite() : texturePath(""), rectangle(0.0f), rotation(0), color(255, 255, 255, 255) {}
    Sprite(std::string TexturePath, glm::vec4 &Rectangle) : texturePath(TexturePath), rectangle(Rectangle), rotation(0.0f), color(255, 255, 255, 255) {}
    Sprite(std::string TexturePath, glm::vec4 &Rectangle, int Rotation) : texturePath(TexturePath), rectangle(Rectangle), rotation(Rotation), color(255, 255, 255, 255) {}
    Sprite(std::string TexturePath, glm::vec4 &Rectangle, int Rotation, ColorRGBA8 Color) : texturePath(TexturePath), rectangle(Rectangle), rotation(Rotation), color(Color) {}
    
    std::string texturePath;
    glm::vec4 rectangle;
    ColorRGBA8 color;
    float rotation;
};

#endif
