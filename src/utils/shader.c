#include "shader.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "../core/types.h"
#include <stdlib.h>
#include <stdio.h>

GLuint LoadShaders(const char *vertex_file_path, const char *fragment_file_path)
{

    // Create the shaders
    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    // Read the Vertex Shader code from the file
    FILE *fptr = fopen(vertex_file_path, "r");
    if (fptr == NULL)
    {
        printf("Could not open file: %s", vertex_file_path);
        return 1;
    };
    fseek(fptr, 0L, SEEK_END);
    u64 shaderFileSize = ftell(fptr);
    fseek(fptr, 0L, SEEK_SET);

    char *shaderCode = malloc(shaderFileSize);
    CLEAR_MEMORY_ARRAY(shaderCode, shaderFileSize);
    fread(shaderCode, shaderFileSize, 1, fptr);
    fclose(fptr);

    // Read the Fragment Shader code from the file
    FILE *fptr2 = fopen(fragment_file_path, "r");
    if (fptr2 == NULL)
    {
        printf("Could not open file: %s", fragment_file_path);
        return 1;
    };
    fseek(fptr2, 0L, SEEK_END);
    u64 shaderFileSize2 = ftell(fptr2);
    fseek(fptr2, 0L, SEEK_SET);

    char *fragmentShaderCode = malloc(shaderFileSize2);
    CLEAR_MEMORY_ARRAY(fragmentShaderCode, shaderFileSize2);
    fread(fragmentShaderCode, shaderFileSize2, 1, fptr2);
    fclose(fptr2);

    GLint Result = GL_FALSE;
    int InfoLogLength;

    // Compile Vertex Shader
    printf("Compiling shader : %s\n", vertex_file_path);
    glShaderSource(VertexShaderID, 1, &shaderCode, NULL);
    glCompileShader(VertexShaderID);

    // Check Vertex Shader
    glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0)
    {
        char *error = malloc(sizeof(char) * (InfoLogLength + 1));
        glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, error);
        printf("%s\n", error);
    }

    // Compile Fragment Shader
    printf("Compiling shader : %s\n", fragment_file_path);
    glShaderSource(FragmentShaderID, 1, &fragmentShaderCode, NULL);
    glCompileShader(FragmentShaderID);

    // Check Fragment Shader
    glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0)
    {
        char *error = malloc(sizeof(char) * (InfoLogLength + 1));
        glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, error);
        printf("%s\n", error);
    }

    // Link the program
    printf("Linking program\n");
    GLuint ProgramID = glCreateProgram();
    glAttachShader(ProgramID, VertexShaderID);
    glAttachShader(ProgramID, FragmentShaderID);
    glLinkProgram(ProgramID);

    // Check the program
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0)
    {
        char *error = malloc(sizeof(char) * (InfoLogLength + 1));
        glGetShaderInfoLog(ProgramID, InfoLogLength, NULL, error);
        printf("%s\n", error);
    }

    glDetachShader(ProgramID, VertexShaderID);
    glDetachShader(ProgramID, FragmentShaderID);

    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);

    return ProgramID;
}
