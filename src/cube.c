#include "cube.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "cglm/cglm.h"
#include <stdio.h>

GLuint vertexbuffer;
GLuint uvbuffer;

float horizontalAngle = 3.14f;
// Initial vertical angle : none
float verticalAngle = 0.0f;
double lastTime; // For like time difference

void createCube()
{
    lastTime = glfwGetTime();

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    static const GLfloat g_uv_buffer_data[] = {
        0.0f, 1.0f - 0,
        0.0f, 1.0f - 0,
        0.0f, 1.0f - 0,
        0.0f, 1.0f - 0,
        0.0f, 1.0f - 0,
        0.0f, 1.0f - 0,
        0.0f, 1.0f - 0,
        0.0f, 1.0f - 0,
        0.0f, 1.0f - 0,
        0.0f, 1.0f - 0,
        0.0f, 1.0f - 0,
        0.0f, 1.0f - 0,
        0.0f, 1.0f - 0,
        0.0f, 1.0f - 0,
        0.0f, 1.0f - 0,
        0.0f, 1.0f - 0,
        0.0f, 1.0f - 0,
        0.0f, 1.0f - 0.,
        0.0f, 1.0f - 0.,
        0.0f, 1.0f - 0.,
        0.0f, 1.0f - 0.,
        0.0f, 1.0f - 0.,
        0.0f, 1.0f - 0.,
        0.0f, 1.0f - 0.,
        0.0f, 1.0f - 0.,
        0.0f, 1.0f - 0.,
        0.0f, 1.0f - 0.,
        0.0f, 1.0f - 0.,
        0.0f, 1.0f - 0.,
        0.0f, 1.0f - 0.,
        0.0f, 1.0f - 0,
        0.0f, 1.0f - 0,
        0.0f, 1.0f - 0,
        0.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 1.0f};

    static const GLfloat g_vertex_buffer_data_cube[] = {
        -1.0f, -1.0f, -1.0f, // triangle 1 : begin
        -1.0f, -1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f, // triangle 1 : end
        1.0f, 1.0f, -1.0f, // triangle 2 : begin
        -1.0f, -1.0f, -1.0f,
        -1.0f, 1.0f, -1.0f, // triangle 2 : end
        1.0f, -1.0f, 1.0f,
        -1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, 1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, -1.0f,
        1.0f, -1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f,
        1.0f, -1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, 1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, -1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, -1.0f,
        -1.0f, 1.0f, -1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, -1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, -1.0f, 1.0f};

    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data_cube), g_vertex_buffer_data_cube, GL_STATIC_DRAW);

    glGenBuffers(1, &uvbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);
}

void cube(GLuint Texture, GLuint TextureID)
{
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
        0.0f,     // attribute 0. No particular reason for0.0f, but must match the layout in the shader.
        3,        // size
        GL_FLOAT, // type
        GL_FALSE, // normalized?
        0.0f,     // stride
        (void *)0 // array buffer offset
    );
    // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0.0f, 12 * 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
    glDisableVertexAttribArray(0);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
    glVertexAttribPointer(
        1,        // attribute. No particular reason for 1, but must match the layout in the shader.
        3,        // size
        GL_FLOAT, // type
        GL_FALSE, // normalized?
        0.0f,     // stride
        (void *)0 // array buffer offset
    );

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, Texture);
    // Set our "myTextureSampler" sampler to use Texture Unit 0
    glUniform1i(TextureID, 0);
}

void spinCube(GLuint programID, GLuint MatrixID)
{
    // Compute time difference between current and last frame
    double currentTime = glfwGetTime();
    float deltaTime = currentTime - lastTime;

    // Direction
    mat4 direction;
    horizontalAngle += deltaTime * 0.8f;
    verticalAngle -= deltaTime * 0.2f;

    vec3 anglesIn = {horizontalAngle, verticalAngle, 0.0f};
    glm_euler(
        anglesIn,
        direction);

    mat4 Projection;
    float angle = 45.0f;
    glm_make_rad(&angle);

    glm_perspective(angle, 4.0f / 3.0f, 0.1f, 100.0f, Projection);

    // Camera matrix
    vec3 cameraPosition = {5.0f, 3.0f, 3.0f};
    vec3 cameraTarget = {0.0f, 0.0f, 0.0f};
    vec3 cameraUp = {0.0f, -1.0f, 0.0f};
    mat4 View;
    vec3 posAndDirection;
    glm_vec3_add(cameraTarget, anglesIn, posAndDirection);
    glm_lookat(
        cameraPosition, // Camera is at (4,3,3), in World Space
        cameraTarget,   // and looks at the origin
        cameraUp,       // Head is up (set to0.0f,-1,0 to look upside-down)
        View            // target matrix
    );
    // Model matrix
    mat4 Model;
    mat4 projectAndView;
    mat4 Position;
    mat4 MVP;
    glm_mat4_identity(Model);

    glm_mat4_mul(Projection, View, projectAndView);
    glm_mat4_mul(projectAndView, Model, Position);
    glm_mat4_mul(Position, direction, MVP);

    glUseProgram(programID);
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

    lastTime = glfwGetTime();
}