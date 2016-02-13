//
//  RenderableObject.cpp
//  OpenGL Renderer
//
//  Created by John Asper on 2/11/16.
//
//

#include "renderableobject.hpp"

RenderableObject::RenderableObject(){
    
}

RenderableObject::~RenderableObject(){
    
}

void RenderableObject::setName(std::string n){
    name = n;
}

std::string RenderableObject::getName(){
    return name;
}

void RenderableObject::render(GLFWwindow *window, glm::mat4 worldTransform, glm::mat4 view, glm::mat4 proj){
    std::cout << "We shouldn't be here..." << std::endl;
}

void RenderableObject::setMaterial(Material *m){
    material = m;
}