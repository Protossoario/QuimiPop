//
//  GLSLProgram.cpp
//  GraphicsTutorial
//
//  Created by Eduardo Alberto Sanchez Alvarado & Graciela Garcia Diaz on 3/1/15.
//  Copyright (c) 2015 Eduardo Alberto Sanchez Alvarado & Graciela Garcia Diaz. All rights reserved.
//

#include "GLSLProgram.h"

GLSLProgram::GLSLProgram() : m_numAttributes(0), m_programID(0), m_vertexShaderID(0), m_fragmentShaderID(0) {}

GLSLProgram::~GLSLProgram() {}

void GLSLProgram::compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath) {
    m_programID = glCreateProgram();
    
    m_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    if (m_vertexShaderID == 0) {
        fatalError("Vertex shader failed to be created!");
    }
    
    m_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    if (m_fragmentShaderID == 0) {
        fatalError("Fragment shader failed to be created!");
    }
    
    compileShader(vertexShaderFilePath, m_vertexShaderID);
    compileShader(fragmentShaderFilePath, m_fragmentShaderID);
}

void GLSLProgram::linkShaders() {
    glAttachShader(m_programID, m_vertexShaderID);
    glAttachShader(m_programID, m_fragmentShaderID);
    
    glLinkProgram(m_programID);
    
    GLint isLinked = 0;
    glGetProgramiv(m_programID, GL_LINK_STATUS, (int *)&isLinked);
    if (isLinked == GL_FALSE) {
        GLint maxLength = 0;
        glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &maxLength);
        
        std::vector<GLchar> errorLog(maxLength);
        glGetProgramInfoLog(m_programID, maxLength, &maxLength, &errorLog[0]);
        
        glDeleteProgram(m_programID);
        glDeleteShader(m_vertexShaderID);
        glDeleteShader(m_fragmentShaderID);
        
        printf("%s\n", &errorLog[0]);
        fatalError("Shaders failed to link!");
    }
    
    glDetachShader(m_programID, m_vertexShaderID);
    glDetachShader(m_programID, m_fragmentShaderID);
    glDeleteShader(m_vertexShaderID);
    glDeleteShader(m_fragmentShaderID);
}

void GLSLProgram::addAttribute(const std::string &attributeName) {
    glBindAttribLocation(m_programID, m_numAttributes++, attributeName.c_str());
}

void GLSLProgram::use() {
    glUseProgram(m_programID);
    for (int i = 0; i < m_numAttributes; i++) {
        glEnableVertexAttribArray(i);
    }
}

void GLSLProgram::unuse() {
    glUseProgram(0);
    for (int i = 0; i < m_numAttributes; i++) {
        glDisableVertexAttribArray(i);
    }
}

GLint GLSLProgram::getUniformLocation(const std::string &uniformName) {
    GLint location = glGetUniformLocation(m_programID, uniformName.c_str());
    if (location == GL_INVALID_INDEX) {
        fatalError("Uniform " + uniformName + " not found in shader!");
    }
    return location;
}

void GLSLProgram::compileShader(const std::string &filePath, const GLuint shaderID) {
    std::ifstream shaderFile(filePath);
    if (shaderFile.fail()) {
        perror(filePath.c_str());
        fatalError("Failed to open " + filePath);
    }
    
    std::string fileContents = "";
    std::string line;
    
    while (std::getline(shaderFile, line)) {
        fileContents += line + "\n";
    }
    
    shaderFile.close();
    
    const char* contentsPtr = fileContents.c_str();
    glShaderSource(shaderID, 1, &contentsPtr, nullptr);
    
    glCompileShader(shaderID);
    
    GLint success = 0;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE) {
        GLint maxLength = 0;
        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);
        
        std::vector<GLchar> errorLog(maxLength);
        glGetShaderInfoLog(shaderID, maxLength, &maxLength, &errorLog[0]);
        
        glDeleteShader(shaderID);
        
        printf("%s\n", &errorLog[0]);
        fatalError("Shader " + filePath + " failed to compile!");
    }
}