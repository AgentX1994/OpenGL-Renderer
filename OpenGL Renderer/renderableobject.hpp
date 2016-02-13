//
//  RenderableObject.hpp
//  OpenGL Renderer
//
//  Created by John Asper on 2/11/16.
//
//

#ifndef RenderableObject_hpp
#define RenderableObject_hpp

#include "main.hpp"
#include "material.hpp"

class RenderableObject {
private:
    std::string name;
    
protected:
    Material *material;
    
public:
    
    // Default Constructor
    RenderableObject();
    
    // Default Destructor
    ~RenderableObject();
    
    void setName(std::string n);
    std::string getName();
    
    void setMaterial(Material *m);
    
    // Render this object
    virtual void render(GLFWwindow *window, glm::mat4 worldTransform, glm::mat4 view, glm::mat4 proj);
};

#endif /* RenderableObject_hpp */
