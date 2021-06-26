#ifndef __TEXTURE_H
#define __TEXTURE_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GL/glext.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>


#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII

#define TEX_BMP 1
#define TEX_DDS 2

class Texture {
private:
    GLuint m_texture_id{0};
    unsigned int m_image_size;
    unsigned int m_width, m_height;
    GLuint m_uniform;
    // RGB data
    int fileExtension(const char * imagepath) const;
    void Init(GLuint programID);

public:
    Texture();
    Texture(const char * imagepath, GLuint programID);
    Texture(const unsigned char * RGB_buffer, const unsigned int width, const unsigned int height, GLuint programID);
    Texture(const float * data_buffer, unsigned int db_length, const unsigned int width, const unsigned int height, GLuint programID);
    Texture(Texture & other) = delete;
    Texture(Texture && other);
    ~Texture();
    bool loadImage(const char * imagepath);
    bool loadBMP(const char * imagepath);
    bool loadDDS(const char * imagepath);
    GLuint getTextureID();
    unsigned int getWidth();
    unsigned int getHeight();
    void bind();



};

#endif