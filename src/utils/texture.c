#include "texture.h"
#include "glad/glad.h"
#include <stdlib.h>
#include <stdio.h>

GLuint loadBMP_custom(const char *imagepath)
{
    printf("Reading image %s\n", imagepath);
    // Data read from the header of the BMP file
    unsigned char header[54]; // Each BMP file begins by a 54-bytes header
    unsigned int dataPos;     // Position in the file where the actual data begins
    unsigned int imageSize;   // Size of the data
    unsigned int width, height;
    // Actual RGB data
    unsigned char *data;

    // Open the file
    FILE *file = fopen(imagepath, "rb");
    if (!file) // Check if file exists
    {
        printf("%s could not be opened. Are you in the right directory ? Don't forget to read the FAQ !\n", imagepath);
        getchar();
        return 0;
    }

    // Read the header, i.e. the 54 first bytes
    fread(header, 1, 54, file);

    /*
        // Read the Vertex Shader code from the file
        FILE *fptr = fopen(imagepath, "r");
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
        fclose(fptr);*/

    // Check if this is a BMP file
    if (header[0] != 'B' || header[1] != 'M')
    {
        printf("%s is not a correct BMP file\n", imagepath);
        return 0;
    }

    // Make sure this is a 24bpp file
    if (*(int *)&(header[0x1E]) != 0)
    {
        printf("Not a correct BMP file\n");
        fclose(file);
        return 0;
    }
    if (*(int *)&(header[0x1C]) != 24)
    {
        printf("Not a correct BMP file\n");
        fclose(file);
        return 0;
    }

    // Read the information about the image
    dataPos = *(int *)&(header[0x0A]);
    imageSize = *(int *)&(header[0x22]);
    width = *(int *)&(header[0x12]);
    height = *(int *)&(header[0x16]);

    // Some BMP files are misformatted, guess missing information
    if (imageSize == 0)
        imageSize = width * height * 3; // 3 : one byte for each Red, Green and Blue component
    if (dataPos == 0)
        dataPos = 54; // The BMP header is done that way
    // Allocate memory for the image data
    data = (unsigned char *)malloc(imageSize);

    // Read the actual data from the file into the buffer
    fread(data, 1, imageSize, file);

    // Everything is in memory now, so close the file !
    fclose(file);

    // Create one OpenGL texture
    GLuint textureID;
    glGenTextures(1, &textureID);

    // "Bind" the newly created texture : all future texture functions will modify this texture
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Give the image to OpenGL
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glGenerateMipmap(GL_TEXTURE_2D);

    // Return the ID of the texture we just created
    return textureID;
}
