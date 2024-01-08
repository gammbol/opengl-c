#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <glad/glad.h>

#include "shaderlib.h"

// TODO: add comments
void checkCompileErrors(unsigned int shaderID, const char* type)
{
    int success;
    char infoLog[1024];
    if (strcmp(type, "PROGRAM") != 0)
    {
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shaderID, 1024, NULL, infoLog);
            printf("ERROR::SHADER_COMPILATION_ERROR of type: %s\n%s\n", type, infoLog);
        }
    }
    else
    {
        glGetProgramiv(shaderID, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shaderID, 1024, NULL, infoLog);
            printf("ERROR::PROGRAM_LINKING_ERROR of type: %s\n%s\n", type, infoLog);
        }
    }
}

SHADER_ST shaderInit(const char* vertexPath, const char* fragmentPath)
{
    char* vertexCode = malloc(sizeof(char) * 512 * 1);
    char* fragmentCode = malloc(sizeof(char) * 512 * 1);

    char* buffer = malloc(512);

    FILE* fp = fopen(vertexPath, "r");
    if (fp)
    {
        int count = 1;
        while (fgets(buffer, 512, fp) != NULL)
        {
            vertexCode = realloc(vertexCode, sizeof(char) * 512 * count);
            if (vertexCode)
            {
                if (count == 1)
                    strcpy(vertexCode, buffer);
                else
                    strcat(vertexCode, buffer);
                count++;
            }
            else
            {
                printf("ERROR::SHADER::VERTEX::ALLOCATION_FAILED\n");
                exit(-2);
            }
        }
    }
    else
    {
        printf("ERROR::SHADER::VERTEX::FILE_NOT_SUCCESSFULLY_READ\n");
        exit(-1);
    }

    fp = fopen(fragmentPath, "r");
    if (fp)
    {
        int count = 1;
        while (fgets(buffer, 512, fp) != NULL)
        {
            fragmentCode = realloc(fragmentCode, sizeof(char) * 512 * count);
            if (fragmentCode)
            {
                if (count == 1)
                    strcpy(fragmentCode, buffer);
                else
                    strcat(fragmentCode, buffer);
                count++;
            }
            else
            {
                printf("ERROR::SHADER::FRAGMENT::ALLOCATION_FAILED\n");
                exit(-2);
            }
        }
    }
    else
    {
        printf("ERROR::SHADER::FRAGMENT::FILE_NOT_SUCCESSFULLY_READ\n");
        exit(-1);
    }
    fclose(fp);

    SHADER_ST shader = {
        .vertexCode = vertexCode,
        .fragmentCode = fragmentCode
    };

    unsigned int vertex, fragment;

    // vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &shader.vertexCode, NULL);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");

    // fragment shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &shader.fragmentCode, NULL);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");

    // shader program
    shader.ID = glCreateProgram();
    glAttachShader(shader.ID, vertex);
    glAttachShader(shader.ID, fragment);
    glLinkProgram(shader.ID);
    checkCompileErrors(shader.ID, "PROGRAM");

    // delete the shaders
    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return shader;
}

void use(SHADER_ST* shader)
{
    glUseProgram(shader->ID);
}

void setBool(SHADER_ST* shader, const char* name, bool value)
{
    glUniform1i(glGetUniformLocation(shader->ID, name), (int)value);
}
void setInt(SHADER_ST* shader, const char* name, int value)
{
    glUniform1i(glGetUniformLocation(shader->ID, name), value);
}
void setFloat(SHADER_ST* shader, const char* name, float value)
{
    glUniform1f(glGetUniformLocation(shader->ID, name), value);
}


