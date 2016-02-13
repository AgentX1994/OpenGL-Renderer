//
//  material.cpp
//  OpenGL Renderer
//
//  Created by John Asper on 2/11/16.
//
//

#include "material.hpp"

Material::Material(){
    
}

Material::~Material(){
    
}

void Material::bind(){
    shader->use();
}

void Material::unbind(){
    shader->unuse();
}

void Material::setUniforms(){
    
}

unsigned int Material::getShaderID(){
    return shader->getID();
}