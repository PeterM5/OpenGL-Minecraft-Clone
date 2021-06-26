#ifndef __TEXT_H
#define __TEXT_H
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include "texture.h"
#include "shader.h"

class Text {
private:
    Texture m_texture;
    GLuint m_VBO_id, m_UVBO_id;
    Shader m_shader_program_id;
    GLuint m_uniform_id;

public:
    Text(GLuint programID, const char * fontpath);
    ~Text();

    void printText(const char * text, int x, int y, int size);
};

#endif