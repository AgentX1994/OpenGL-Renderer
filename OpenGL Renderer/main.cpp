//
//  main.cpp
//  OpenGL Renderer
//
//  Created by John Asper on 2/13/16.
//
//

#include "main.hpp"
#include "camera.hpp"
#include "scenenode.hpp"
#include "defaultmaterial.hpp"
#include "meshobject.hpp"

void error_callback(int error, const char *description){
    std::cerr << "GLFW ERROR:" << description << std::endl;
}

const float maxCamSpeed = 10.0f;
float camXSpeed = 0;
float camYSpeed = 0;
float camZSpeed = 0;

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods){
    switch (key) {
        case GLFW_KEY_ESCAPE:
            if (action == GLFW_RELEASE) {
                glfwSetWindowShouldClose(window, GL_TRUE);
            }
            break;
        case GLFW_KEY_W:
            if (action == GLFW_PRESS) {
                camZSpeed = maxCamSpeed;
            } else if (action == GLFW_RELEASE){
                camZSpeed = 0;
            }
            break;
        case GLFW_KEY_S:
            if (action == GLFW_PRESS) {
                camZSpeed = -maxCamSpeed;
            } else if (action == GLFW_RELEASE){
                camZSpeed = 0;
            }
            break;
        case GLFW_KEY_A:
            if (action == GLFW_PRESS) {
                camXSpeed = -maxCamSpeed;
            } else if (action == GLFW_RELEASE){
                camXSpeed = 0;
            }
            break;
        case GLFW_KEY_D:
            if (action == GLFW_PRESS){
                camXSpeed = maxCamSpeed;
            } else if (action == GLFW_RELEASE){
                camXSpeed = 0;
            }
            break;
        case GLFW_KEY_R:
            if (action == GLFW_PRESS) {
                camYSpeed = maxCamSpeed;
            } else if (action == GLFW_RELEASE){
                camYSpeed = 0;
            }
            break;
        case GLFW_KEY_F:
            if (action == GLFW_PRESS) {
                camYSpeed = -maxCamSpeed;
            } else if (action == GLFW_RELEASE) {
                camYSpeed = 0;
            }
            break;
            
        default:
            break;
    }
}

int main(int argc, const char * argv[]) {
    
    // Initialize glfw
    if (!glfwInit()){
        std::cerr << "Failed to initialize glfw" << std::endl;
        exit(EXIT_FAILURE);
    }
    
    // Set the error callback for glfw
    glfwSetErrorCallback(error_callback);
    
    // Set window settings
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    
    GLFWwindow *window = glfwCreateWindow(800,600, "OpenGL Renderer", NULL, NULL);
    
    if (!window) {
        std::cerr << "Could not create glfw window!" << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    
    glfwSetKeyCallback(window, key_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    float ratio = width / (float) height;
    
    Camera cam(glm::vec3(0,0,-2));
    cam.setProjMatrix(ratio);
    
    DefaultMaterial m(glm::vec3(.2f,.2f,.9f));
    
    MeshObject cube;
    cube.setMaterial(&m);
    
    SceneNode cubeNode(&cube);
    cubeNode.setTransform(glm::scale(glm::mat4(), glm::vec3(2)));
    
    double lastFrameTime = glfwGetTime();
    double xpos, ypos;
    
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        
        double currentFrameTime = glfwGetTime();
        
        double delta = currentFrameTime - lastFrameTime;
        
        lastFrameTime = currentFrameTime;
        
        cam.translate(glm::vec3(delta * camXSpeed, delta * camYSpeed, delta * camZSpeed));
        
        glfwGetCursorPos(window, &xpos, &ypos);
        
        // Cursor rotation is currently broken.
        //cam.rotateFromCursor(2*xpos/width - 1, 2*ypos/height - 1);
        
        cubeNode.render(window, cam.getViewMatrix(), cam.getProjMatrix());
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
