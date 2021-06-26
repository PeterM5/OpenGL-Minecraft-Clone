#ifndef _QUAD_H
#define __QUAD_H

#include <iostream>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>
#include "texture.h"
#include "text.h"


static const GLfloat quad_vertex_data[12] {
    0, 1, 0,
    0, 1, 1,
    1, 1, 1,
    1, 1, 0
};

static const GLfloat quad_uv_buffer_data[8] {
    0, 0,
    0, 1,
    1, 1,
    1, 0
};

static const GLushort quad_indices_data[6] {
    0, 1, 2,
    0, 2, 3
};

class Quad {
private:
    GLuint m_VAO; // Vertex Array Object
    GLuint m_VBO; // Vertex Buffer Object
    GLuint m_UVBO; // UV Buffer Object
    GLuint m_IDO; // Index Buffer Object

    Texture *m_texture;

    float m_xpos;
    float m_ypos;
    float m_zpos;

public:
    Quad(GLuint programID, Texture *texture, float xpos = 0.0f, float ypos = 0.0f, float zpos = 0.0f);
    Quad(const Quad & other) = delete; // Remove copy constructor
    Quad(Quad && other); // Move constructor
    ~Quad();
    void Render(GLuint MVP_handle, glm::mat4 &VP);
};

#endif