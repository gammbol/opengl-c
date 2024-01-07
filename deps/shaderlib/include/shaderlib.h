//
// Created by gammb on 1/6/2024.
//

#ifndef OPENGL_LEARN_SHADERLIB_H
#define OPENGL_LEARN_SHADERLIB_H

#include <stdbool.h>

typedef struct {
    unsigned int ID;
    const char* vertexCode;
    const char* fragmentCode;
} SHADER_ST;

// read and build the shader
SHADER_ST shaderInit(const char* vertexPath, const char* fragmentPath);

// use/activate the shader
void use(SHADER_ST *shader);

// utility uniform functions
void setBool(SHADER_ST* shader, const char* name, bool value);
void setInt(SHADER_ST* shader, const char* name, int value);
void setFloat(SHADER_ST* shader, const char* name, float value);


#endif //OPENGL_LEARN_SHADERLIB_H
