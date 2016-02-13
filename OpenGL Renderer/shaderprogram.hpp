//
//  shaderprogram.hpp
//  OpenGL Renderer
//
//  Created by John Asper on 2/11/16.
//
//

#ifndef shaderprogram_hpp
#define shaderprogram_hpp

#include "main.hpp"

class ShaderProgram {
private:
    unsigned int id;
    
    unsigned int shaderID;
    unsigned int shaderVP;
    unsigned int shaderFP;
    
    void init(const char *vsFile, const char *fsFile);
    
protected:
    
public:
    // Generic Constructor
    ShaderProgram();
    
    // Constructs a shader that uses the given shaders
    ShaderProgram(const char *vsFile, const char *fsFile);
    
    // Copy Constructor. This class cannot be copied so it cannot be defined
    ShaderProgram(const ShaderProgram &s);
    
    ~ShaderProgram();
    
    // Use this shader when rendering
    void use();
    
    // Stop using this shader when rendering
    void unuse();
    
    unsigned int getID();
    
};

#endif /* shaderprogram_hpp */
