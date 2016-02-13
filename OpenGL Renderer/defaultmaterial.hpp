//
//  defaultmaterial.hpp
//  OpenGL Renderer
//
//  Created by John Asper on 2/11/16.
//
//

#ifndef defaultmaterial_hpp
#define defaultmaterial_hpp

#include "main.hpp"
#include "material.hpp"
#include "shaderprogram.hpp"

class DefaultMaterial: public Material {
private:
    glm::vec3 color;
protected:
    
public:
    // Default Constructor: gives the material a white color
    DefaultMaterial();
    
    // Constructor: makes the material the given color
    DefaultMaterial(glm::vec3 c);
    
    // Copy Constructor: This class cannot be copied so this must not be defined
    DefaultMaterial(const DefaultMaterial &m);
    
    // Destructor
    ~DefaultMaterial();
    
    // Set the required uniforms
    void setUniforms();
};
#endif /* defaultmaterial_hpp */
