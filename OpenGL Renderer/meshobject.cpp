//
//  MeshObject.cpp
//  OpenGL Renderer
//
//  Created by John Asper on 2/11/16.
//
//

#include "meshobject.hpp"

// Default constructor, sets the mesh to cube
MeshObject::MeshObject(){
    vertexCount = 36;
    glm::vec3* vertices = new glm::vec3[36];  // Vertices for our square
    triCount = vertexCount/3;
    
    glm::vec3 v0(0.5f,0.5f,-0.5f);
    glm::vec3 v1(-0.5f,0.5f,-0.5f);
    glm::vec3 v2(-0.5f,-0.5f,-0.5f);
    glm::vec3 v3(0.5f,-0.5f,-0.5f);
    
    glm::vec3 v4(0.5f,-0.5f,0.5f);
    glm::vec3 v5(0.5f,0.5f,0.5f);
    glm::vec3 v6(-0.5f,0.5f,0.5f);
    glm::vec3 v7(-0.5f,-0.5f,0.5f);
    
    vertices[0] = v0;
    vertices[1] = v1;
    vertices[2] = v2;
    
    vertices[3] = v2;
    vertices[4] = v3;
    vertices[5] = v0;
    
    vertices[6] = v0;
    vertices[7] = v3;
    vertices[8] = v3;
    
    vertices[9] = v4;
    vertices[10] = v5;
    vertices[11] = v0;
    
    vertices[12] = v0;
    vertices[13] = v5;
    vertices[14] = v6;
    
    vertices[15] = v6;
    vertices[16] = v1;
    vertices[17] = v0;
    
    vertices[18] = v1;
    vertices[19] = v6;
    vertices[20] = v7;
    
    vertices[21] = v7;
    vertices[22] = v2;
    vertices[23] = v1;
    
    vertices[24] = v7;
    vertices[25] = v4;
    vertices[26] = v3;
    
    vertices[27] = v3;
    vertices[28] = v2;
    vertices[29] = v7;
    
    vertices[30] = v4;
    vertices[31] = v7;
    vertices[32] = v6;
    
    vertices[33] = v6;
    vertices[34] = v5;
    vertices[35] = v4;
    
    glGenVertexArrays(1, (GLuint *)vaoID); // Create our Vertex Array Object
    glBindVertexArray(vaoID[0]); // Bind our Vertex Array Object so we can use it
    
    glGenBuffers(1, (GLuint *)vboID); // Generate our Vertex Buffer Object
    glBindBuffer(GL_ARRAY_BUFFER, vboID[0]); // Bind our Vertex Buffer Object
    static_assert(sizeof(glm::vec3) == sizeof(GLfloat) * 3, "Platform doesn't support this directly.");
    glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(glm::vec3), &vertices[0][0], GL_STATIC_DRAW); // Set the size and data of our VBO and set it to STATIC_DRAW
    
    glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0); // Set up our vertex attributes pointer
    
    glEnableVertexAttribArray(0); // Disable our Vertex Array Object
    glBindVertexArray(0); // Disable our Vertex Buffer Object
    
    delete [] vertices; // Delete our vertices from memory
}

// Constructor, sets the object to the given mesh
// Unfinished!
MeshObject::MeshObject(char *mesh){
    // TODO
}

// Render this object
void MeshObject::render(GLFWwindow *window, glm::mat4 worldTransform, glm::mat4 view, glm::mat4 proj){
    glCheckErrors("start of render");
    
    material->bind();
    
    glCheckErrors("after binding shaders");
    
    material->setUniforms();
    
    glCheckErrors("after setting color");
    
    int projectionMatrixLocation = glGetUniformLocation(material->getShaderID(), "mProj"); // Get the location of our projection matrix in the shader
    int viewMatrixLocation = glGetUniformLocation(material->getShaderID(), "mView"); // Get the location of our view matrix in the shader
    int worldMatrixLocation = glGetUniformLocation(material->getShaderID(), "mWorld"); // Get the location of our world matrix in the shader
    
    glCheckErrors("before setting matrix uniforms");
    
    glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &proj[0][0]); // Send our projection matrix to the shader
    glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &view[0][0]); // Send our view matrix to the shader
    glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &worldTransform[0][0]); // Send our model matrix to the shader
    
    glCheckErrors("beforing binding array");
    
    glBindVertexArray(vaoID[0]); // Bind our Vertex Array Object
    
    glCheckErrors("after binding array");    
    glDrawArrays(GL_TRIANGLES, 0, vertexCount); // Draw our cube
    
    glCheckErrors("after draw call");
    
    glBindVertexArray(0); // Unbind our Vertex Array Object
    
    glCheckErrors("after unbinding array");
    
    material->unbind();
    
    glCheckErrors("after unbinding material");
}