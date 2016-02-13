//
//  sceneNode.hpp
//  OpenGL Renderer
//
//  Implements a scene graph node for the Open GL Renderer
//
//  Created by John Asper on 2/11/16.
//
//

#ifndef sceneNode_hpp
#define sceneNode_hpp

#include "main.hpp"
#include "renderableobject.hpp"

class SceneNode {
private:
    // static variable to hold the next id
    static long idIterator;
    
    long nodeID;
    
    RenderableObject *object; // The object at this node
    glm::mat4 transform; // local transform
    
    glm::mat4 worldTransform; // world transfrom
    
    SceneNode *parent; // The parent of this node. Currently only one supported
    glm::mat4 parentTransform; // Parent's transform
    
    // The children of this node
    std::vector<SceneNode> children;
    
    long getNextID(){
        return idIterator++;
    }
    
protected:
    
public:
    
    inline bool operator==(SceneNode& a){
        return this->getID() == a.getID();
    }
    // Default Constructor. Sets the object to null, and the transform to the identity.
    SceneNode();
    
    // Constructor, sets the object to the given object.
    SceneNode(RenderableObject *o);
    
    // Set this node's object
    void setObject(RenderableObject *o);

    // Update the world transforms of this node and all children
    void updateTransforms();
    
    // Set/Get the local transform
    void setTransform(glm::mat4 t);
    glm::mat4 getTransform();
    
    // Apply a transform
    void applyTransform(glm::mat4 t);
    
    // Get the world transform
    glm::mat4 getWorldTransform();
    
    // Get this node's id
    long getID();
    
    // Add a child to this scene node
    void addChild(SceneNode n);
    
    // Remove a child from this scene node
    void removeChild(SceneNode n);
    
    // Set/Get the parent of this node
    void setParent(SceneNode *n);
    SceneNode *getParent();
    
    // Render this object and all children.
    void render(GLFWwindow *window, glm::mat4 view, glm::mat4 proj);
};

#endif /* sceneNode_hpp */
