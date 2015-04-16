//
//  GLSLProgram.h
//  GraphicsTutorial
//
//  Created by Eduardo Alberto Sanchez Alvarado & Graciela Garcia Diaz on 3/1/15.
//  Copyright (c) 2015 Eduardo Alberto Sanchez Alvarado & Graciela Garcia Diaz. All rights reserved.
//

#ifndef __GraphicsTutorial__GLSLProgram__
#define __GraphicsTutorial__GLSLProgram__

//#include <OpenGL/gl3.h>
#include <Windows.h>
#include <GL/glew.h>
#include <fstream>
#include <string>
#include <vector>
#include "Errors.h"

class GLSLProgram {
public:
    GLSLProgram();
    ~GLSLProgram();
    
    void compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);
    void linkShaders();
    void addAttribute(const std::string& attributeName);
    void use();
    void unuse();
    
    GLint getUniformLocation(const std::string& uniformName);
    
private:
    int m_numAttributes;
    
    void compileShader(const std::string& filePath, const GLuint shaderID);
    
    GLuint m_programID;
    
    GLuint m_vertexShaderID;
    GLuint m_fragmentShaderID;
};

#endif /* defined(__GraphicsTutorial__GLSLProgram__) */
