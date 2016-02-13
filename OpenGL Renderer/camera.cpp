//
//  camera.cpp
//  OpenGL Renderer
//
//  Created by John Asper on 2/10/16.
//
//

#include "camera.hpp"

// Stamdard Constructor, creates camera at (0,0,0) looking towards +z with 16:9 proj ratio.
Camera::Camera(){
    Camera(glm::vec3(0,0,0));
}

// Constructor with position, looking towards +z.
Camera::Camera(glm::vec3 p){
    Camera(p, glm::vec3(0,0,1));
}

// Constructor with position and view vector
Camera::Camera(glm::vec3 p, glm::vec3 v){
    setPos(p);
    setViewDir(v);
    refreshViewMatrix();
    setProjMatrix(16.0f/9.0f);
    angleX = 0;
    angleY = 0;
}

// Currently the viewing direction is not actually used. This will be changed later.
void Camera::refreshViewMatrix(){
    viewMat = glm::translate(glm::mat4(1.0f), pos);
}

// Set/get camera position
void Camera::setPos(glm::vec3 p){
    pos = p;
}
glm::vec3 Camera::getPos(){
    return pos;
}

// Set/get camera viewing direction
void Camera::setViewDir(glm::vec3 v){
    //viewDir = glm::normalize(v);
}
glm::vec3 Camera::getViewDir(){
    return pos;//viewDir;
}

// Set camera to look at given position
void Camera::setLookAt(glm::vec3 pos){
    //viewDir = glm::normalize(this->pos-pos);
    refreshViewMatrix();
}

// Returns the view matrix
glm::mat4 Camera::getViewMatrix(){
    return viewMat;
}

// Set/Return the Projection Matrix;
void Camera::setProjMatrix(float ratio){
    projMat = glm::perspective(fov, ratio, zNear, zFar);
}
glm::mat4 Camera::getProjMatrix(){
    return projMat;
}

// Move the camera along its axes.
// NOTE: these will be in the camera's local frame.
void Camera::translate(glm::vec3 v){
    pos += v;
    refreshViewMatrix();
}

const float mouseSensitivityX = .75f;
const float mouseSensitivityY = .5f;

// Rotate the camera by the normalized mouse position
// -1 < x, y < 1
void Camera::rotateFromCursor(double x, double y){
    angleX += (float)x * mouseSensitivityX;
    angleY += (float)y * mouseSensitivityY;
}


