//
//  MeshObject.hpp
//  OpenGL Renderer
//
//  Implements a mesh object for Open GL Test.
//
//  Created by John Asper on 2/11/16.
//
//

#ifndef MeshObject_hpp
#define MeshObject_hpp

#include "main.hpp"
#include "renderableobject.hpp"
#include "shaderprogram.hpp"

class MeshObject: public RenderableObject {
private:
    int vaoID[1];       // Vertex array ID
    int vboID[1];       // Vertex buffer ID
    int vertexCount;    // number of vertices
    int triCount;       // number of triangles
    
protected:
    
public:
    // Default constructor, sets the mesh to a single square
    MeshObject();
    
    // Constructor, sets the object to the given mesh
    // Unfinished!
    MeshObject(char *mesh);
    
    // Render this object
    void render(GLFWwindow *window, glm::mat4 worldTransform, glm::mat4 view, glm::mat4 proj);
};

#endif /* MeshObject_hpp */
