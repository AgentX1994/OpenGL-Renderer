//
//  utils.hpp
//  OpenGL Renderer
//
//  Created by John Asper on 2/12/16.
//
//

#ifndef utils_hpp
#define utils_hpp

#include "main.hpp"

char *readSource(const char *file);

void mat4PrettyPrint(glm::mat4 m);

void vec3PrettyPrint(glm::vec3 v);

void glCheckErrors(std::string loc);

#endif /* utils_hpp */
