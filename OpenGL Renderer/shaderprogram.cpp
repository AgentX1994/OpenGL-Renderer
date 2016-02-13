//
//  shaderprogram.cpp
//  OpenGL Renderer
//
//  Created by John Asper on 2/11/16.
//
//

#include "shaderprogram.hpp"

// Generic Constructor
ShaderProgram::ShaderProgram(){
    
}

// Constructs a shader that uses the given shaders
ShaderProgram::ShaderProgram(const char *vsFile, const char *fsFile){
    init(vsFile, fsFile);
}

ShaderProgram::~ShaderProgram(){
    glDeleteShader(shaderFP);
    glDeleteShader(shaderVP);
    glDeleteProgram(shaderID);
}

void ShaderProgram::init(const char *vsFile, const char *fsFile){
    // Create the shaders
    std::cout << "using vertex shader: " << vsFile << std::endl;
    std::cout << "using fragment shader: " << fsFile << std::endl;
    
    shaderVP = glCreateShader(GL_VERTEX_SHADER);
    shaderFP = glCreateShader(GL_FRAGMENT_SHADER);
    
    const char *vp = readSource(vsFile);
    const char *fp = readSource(fsFile);
    
    if (vp == NULL || fp == NULL) {
        std::cerr << "ShaderProgram::Init ERROR: ONE OR BOTH FILES NOT FOUND!" << std::endl;
        exit(EXIT_FAILURE);
    }
    
    // Set the source codes
    glShaderSource(shaderVP, 1, &vp, 0);
    glShaderSource(shaderFP, 1, &fp, 0);
    
    delete [] vp;
    delete [] fp;
    
    // Compile the shader source
    glCompileShader(shaderVP);
    
    // Check for errors
    GLint isCompiled = 0;
    glGetShaderiv(shaderVP, GL_COMPILE_STATUS, &isCompiled);
    if(isCompiled == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(shaderVP, GL_INFO_LOG_LENGTH, &maxLength);
        
        // The maxLength includes the NULL character
        std::vector<GLchar> errorLog(maxLength);
        glGetShaderInfoLog(shaderVP, maxLength, &maxLength, &errorLog[0]);
        
        // Provide the infolog in whatever manor you deem best.
        std::cout << "Vertex Shader Compilation Error:" << std::endl;
        for (std::vector<GLchar>::iterator it = errorLog.begin(); it != errorLog.end(); it++) {
            std::cout << *it;
        }
        
        std::cout << std::endl;
        // Exit with failure.
        glDeleteShader(shaderVP); // Don't leak the shader.
        exit(EXIT_FAILURE);
    }
    
    glCompileShader(shaderFP);
    
    isCompiled = 0;
    glGetShaderiv(shaderFP, GL_COMPILE_STATUS, &isCompiled);
    if(isCompiled == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(shaderFP, GL_INFO_LOG_LENGTH, &maxLength);
        
        // The maxLength includes the NULL character
        std::vector<GLchar> errorLog(maxLength);
        glGetShaderInfoLog(shaderFP, maxLength, &maxLength, &errorLog[0]);
        
        // Provide the infolog in whatever manor you deem best.
        std::cout << "Fragment Shader Compilation Error:" << std::endl;
        for (std::vector<GLchar>::iterator it = errorLog.begin(); it != errorLog.end(); it++) {
            std::cout << *it;
        }
        
        std::cout << std::endl;
        // Exit with failure.
        glDeleteShader(shaderVP);
        glDeleteShader(shaderFP); // Don't leak the shader.
        exit(EXIT_FAILURE);
    }
    
    // Create the shader program
    shaderID = glCreateProgram();
   
    // Attach the shaders to the program
    glAttachShader(shaderID, shaderVP);
    glAttachShader(shaderID, shaderFP);
    
    glLinkProgram(shaderID);
    
    GLint isLinked;
    glGetProgramiv(shaderID, GL_LINK_STATUS, &isLinked);
    if (isLinked == GL_FALSE) {
        GLint maxLength;
        glGetProgramiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);
        
        //The maxLength includes the NULL character
        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(shaderID, maxLength, &maxLength, &infoLog[0]);
        
        //The program is useless now. So delete it.
        glDeleteProgram(shaderID);
        
        //Provide the infolog in whatever manner you deem best.
        for (std::vector<GLchar>::iterator it = infoLog.begin(); it != infoLog.end(); it++) {
            std::cout << *it;
        }
        std::cout << std::endl;
        //Exit with failure.
        glDeleteShader(shaderVP);
        glDeleteShader(shaderFP);
        
        exit(EXIT_FAILURE);
    }
    
    glDetachShader(shaderID, shaderVP);
    glDetachShader(shaderID, shaderFP);
    
    glDeleteShader(shaderVP);
    glDeleteShader(shaderFP);
    
    glCheckErrors("After Linking");
    glBindAttribLocation(shaderID, 0, "vert_position");
    glCheckErrors("Bind Attrib");
    std::cout << "Shader Program " << shaderID << ": " << vsFile << " + " << fsFile << std::endl;
}

// Use this shader when rendering
void ShaderProgram::use(){
    if (glIsProgram(shaderID) != GL_TRUE) {
        std::cout << "GL ERROR: THERE IS NO PROGRAM " << shaderID << std::endl;
    }
    glCheckErrors("ShaderProgram::use()1");
    glUseProgram(shaderID);
    glCheckErrors("ShaderProgram::use()2");
}

// Stop using this shader when rendering
void ShaderProgram::unuse(){
    glUseProgram(0);
}

unsigned int ShaderProgram::getID(){
    return shaderID;
}