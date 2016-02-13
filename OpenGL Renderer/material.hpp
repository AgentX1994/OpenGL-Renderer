//
//  material.hpp
//  OpenGL Renderer
//
//  Created by John Asper on 2/11/16.
//
//

#ifndef material_hpp
#define material_hpp

#include "main.hpp"
#include "shaderprogram.hpp"

class Material {
private:
    
protected:
    ShaderProgram *shader;
    
public:
    Material();
    ~Material();
    
    // Copy Constructor. This class cannot be copied so it cannot be defined
    Material(const Material &m);
    
    // Use this material for rendering
    void bind();
    
    // Stop using this material for rendering
    void unbind();
    
    // Set the material uniforms. Overload for different material types
    virtual void setUniforms();
    
    // Get the id of the shader. required to set matrix uniforms for vertex transforms
    unsigned int getShaderID();
};

#endif /* material_hpp */
