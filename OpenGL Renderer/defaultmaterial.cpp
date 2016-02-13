//
//  defaultmaterial.cpp
//  OpenGL Renderer
//
//  Created by John Asper on 2/11/16.
//
//

#include "defaultmaterial.hpp"

const char *vertPath = "/Users/john/Documents/Xcode Projects/OpenGL Renderer/OpenGL Renderer/default.vert";
const char *fragPath = "/Users/john/Documents/Xcode Projects/OpenGL Renderer/OpenGL Renderer/default.frag";

DefaultMaterial::DefaultMaterial(){
    DefaultMaterial(glm::vec3(.9f,.9f,.9f));
}

DefaultMaterial::DefaultMaterial(glm::vec3 c){
    shader = new ShaderProgram(vertPath, fragPath);
    color = c;
}

DefaultMaterial::~DefaultMaterial(){
    delete shader;
}

void DefaultMaterial::setUniforms(){
    int colorLoc = glGetUniformLocation(getShaderID(), "color"); // Get the location of the uniform in the shader
    glUniform3f(colorLoc, color[0], color[1], color[2]); // Set the color
}