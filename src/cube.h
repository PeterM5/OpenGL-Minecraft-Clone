#ifndef __CUBE_H
#define __CUBE_H

#include <iostream>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>
#include "texture_atlas.h"
#include "texture.cpp"
#include "text.h"


static const GLfloat cube_vertex_data[72] {
    // Front
    0, 0, 0, //0
    0, 1, 0, //1
    1, 1, 0, //2
    1, 0, 0, //3

    // Back
    0, 0, 1, //4
    0, 1, 1, //5
    1, 1, 1, //6
    1, 0, 1, //7

    // Left
    0, 0, 1, //8
    0, 1, 1, //9
    0, 1, 0, //10
    0, 0, 0, //11

    // Right
    1, 0, 0, //12
    1, 1, 0, //13
    1, 1, 1, //14
    1, 0, 1, //15

    // Top
    0, 1, 0, //16
    0, 1, 1, //17
    1, 1, 1, //18
    1, 1, 0, //19

    // Bottom
    0, 0, 0, //20
    0, 0, 1, //21
    1, 0, 1, //22
    1, 0, 0  //23
};

static const GLfloat cube_light_data[24]
{
    // Front
    0.5f,
    0.5f,
    0.5f,
    0.5f,

    // Black
    0.5f,
    0.5f,
    0.5f,
    0.5f,

    // Left
    0.5f,
    0.5f,
    0.5f,
    0.5f,

    // Right
    0.5f,
    0.5f,
    0.5f,
    0.5f,

    // Top
    1.0f,
    1.0f,
    1.0f,
    1.0f,

    // Bottom
    0.1f,
    0.1f,
    0.1f,
    0.1f
};


static const GLfloat cube_uv_buffer_data[48] {
    // Front
    0, 0,
    0, 1,
    1, 1,
    1, 0,

    // Back
    1, 0,
    1, 1,
    0, 1,
    0, 0,

    // Left
    0, 0,
    0, 1,
    1, 1,
    1, 0,

    // Right
    0, 0,
    0, 1,
    1, 1,
    1, 0,

    // Top
    0, 0,
    0, 1,
    1, 1,
    1, 0,

    // Bottom
    0, 1,
    0, 0,
    1, 0,
    1, 1
};

static const GLushort cube_indices_data[36] {
    // Front
    2, 1, 0,
    0, 3, 2,

    //Back
    4, 5, 6,
    6, 7, 4,

    // Left
    10, 9, 8,
    11, 10, 8,

    // Right
    14, 13, 12,
    15, 14, 12,

    // Top
    18, 17, 16,
    19, 18, 16,

    // Bottom
    20, 21, 22,
    22, 23, 20
    
};

class Cube {
private:
    GLuint m_VAO; // Vertex Array Object
    GLuint m_VBO; // Vertex Buffer Object
    GLuint m_UVBO; // UV Buffer Object
    GLuint m_LBO; // Light Buffer Object
    GLuint m_IDO; // Index Buffer Object

    TextureAtlas * m_texture_atlas; // Handles obtaining uvs for texture atlas and binding during rendering

    float m_xpos;
    float m_ypos;
    float m_zpos;

public:
    Cube(GLuint programID, TextureAtlas * texture_atlas, unsigned int id, float xpos = 0.0f, float ypos = 0.0f, float zpos = 0.0f);
    Cube(const Cube & other) = delete; // Remove copy constructor
    Cube(Cube && other); // Move constructor
    ~Cube();
    void Render(GLuint MVP_handle, glm::mat4 &VP);
};

#endif