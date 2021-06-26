#ifndef __TEXTURE_ATLAS_H
#define __TEXTURE_ATLAS_H

#include <iostream>
#include <glad/glad.h>
#include "texture.h"

class TextureAtlas {
private:
    Texture m_texture;
    unsigned int m_tile_size;

public:
    TextureAtlas(const char * path, unsigned int m_tile_size, GLuint programID);
    ~TextureAtlas();

    void TransformUV(GLfloat * uvs, unsigned int length, unsigned int id);
    void TransformUV(
        GLfloat * uvs, 
        unsigned int id_front,
        unsigned int id_back,
        unsigned int id_left,
        unsigned int id_right,
        unsigned int id_top,
        unsigned int id_bottom
        );
    void bind();

};

#endif
