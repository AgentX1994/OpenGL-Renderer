//
//  sceneNode.cpp
//  OpenGL Renderer
//
//  Created by John Asper on 2/11/16.
//
//

#include "sceneNode.hpp"

long SceneNode::idIterator = 0;

// Default Constructor. Sets the object to null, and the transform to the identity.
SceneNode::SceneNode(){
    SceneNode(NULL);
}

// Constructor, sets the object to the given object.
SceneNode::SceneNode(RenderableObject *o){
    parent = NULL;
    object = o;
    transform = glm::mat4();
    parentTransform = glm::mat4();
    children = std::vector<SceneNode>();
    updateTransforms();
}

// Set this node's object
void SceneNode::setObject(RenderableObject *o){
    object = o;
}

// Update the transforms of all children
void SceneNode::updateTransforms(){
    if (parent != NULL) {
        worldTransform = parent->getWorldTransform() * transform;
    } else {
        worldTransform = transform;
    }
    
    for (std::vector<SceneNode>::iterator it = children.begin(); it != children.end(); it++){
        it->updateTransforms();
    }
}

// Set/Get the local transform
void SceneNode::setTransform(glm::mat4 t){
    transform = t;
    updateTransforms();
}

glm::mat4 SceneNode::getTransform(){
    return transform;
}

glm::mat4 SceneNode::getWorldTransform(){
    return worldTransform;
}

void SceneNode::applyTransform(glm::mat4 t){
    transform = t * transform;
    updateTransforms();
}

// Get this node's id
long SceneNode::getID(){
    return nodeID;
}

// Add a child to this scene node
void SceneNode::addChild(SceneNode n){
    children.push_back(n);
    n.setParent(this);
    n.updateTransforms();
}

// Remove a child from this scene node
void SceneNode::removeChild(SceneNode n){
    for (std::vector<SceneNode>::iterator it = children.begin(); it != children.end(); it++){
        if (*it == n) {
            it->setParent(NULL);
            it->updateTransforms();
            children.erase(it);
            return;
        }
    }
}

// Set/Get the parent of this node
void SceneNode::setParent(SceneNode *n){
    parent = n;
    updateTransforms();
}
SceneNode *SceneNode::getParent(){
    return parent;
}

// Render this object and all children.
void SceneNode::render(GLFWwindow *window, glm::mat4 view, glm::mat4 proj){
    object->render(window, worldTransform, view, proj);
    
    for (std::vector<SceneNode>::iterator it = children.begin(); it != children.end(); it++){
        it->render(window, view, proj);
    }
}