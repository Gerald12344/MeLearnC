#include "frameRate.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <stdio.h>

int frameCount;
double previousTime;

void startFPSCounter()
{
    previousTime = glfwGetTime();
    frameCount = 0;
}

void calculateFPS()
{
    double currentTime = glfwGetTime();
    frameCount++;
    // If a second has passed.
    if (currentTime - previousTime >= 1.0)
    {
        // Display the frame count here any way you want.
        printf("%d Frames Per Second\n", frameCount);

        frameCount = 0;
        previousTime = currentTime;
    }
}