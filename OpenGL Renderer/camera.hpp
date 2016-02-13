//
//  camera.hpp
//  OpenGL Renderer
//
//  Implements a standard camera for use in 3D rendering.
//
//  Created by John Asper on 2/10/16.
//
//

#ifndef camera_hpp
#define camera_hpp

#include <stdio.h>
#include "main.hpp"

class Camera {
private:
    glm::vec3 pos;      // Position of the camera
    glm::mat4 viewMat;  // View Matrix
    glm::mat4 projMat;  // Projection Matrix
    
    float angleY;       // Angle around the y axis, Yaw
    float angleX;       // Angle around the x axis, Pitch
    
    const float zFar = 100.0f;
    const float zNear = 0.01f;
    const float fov = 60.0f;
    
    void refreshViewMatrix();
    
protected:
    
public:
    // Stamdard Constructor, creates camera at (0,0,0) looking towards +z.
    Camera();
    
    // Constructor with position, looking towards +z.
    Camera(glm::vec3 p);
    
    // Constructor with position and view vector
    Camera(glm::vec3 p, glm::vec3 v);
    
    // Set/get camera position
    void setPos(glm::vec3 p);
    glm::vec3 getPos();
    
    // Set/get camera viewing direction
    void setViewDir(glm::vec3 v);
    glm::vec3 getViewDir();
    
    // Set camera to look at given position
    void setLookAt(glm::vec3 pos);
    
    // Set/Return the view matrix
    void setViewMatrix(glm::mat4 V);
    glm::mat4 getViewMatrix();
    
    // Set/Return the Projection Matrix;
    void setProjMatrix(float ratio);
    glm::mat4 getProjMatrix();
    
    // Move the camera along its axes.
    // NOTE: these will be in the camera's local frame.
    void translate(glm::vec3 v);
    
    // Rotate the camera by the normalized mouse position
    // -1 < x, y < 1
    void rotateFromCursor(double x, double y);
};

#endif /* camera_hpp */
