#ifndef __CHUNK_H
#define __CHUNK_H

#include <cstdint>
#include <vector>
#include "cube.h"
#include <glad/glad.h>

static const GLushort chunk_indices_data[36] {
    // Front
    2, 1, 0,
    0, 3, 2,

    //Back
    0, 1, 2,
    2, 3, 0,

    // Left
    2, 1, 0,
    3, 2, 0,

    // Right
    2, 1, 0,
    3, 2, 0,

    // Bottom 
    2, 1, 0,
    3, 2, 0,

    // Top 
    0, 1, 2,
    2, 3, 0
    
};


class Chunk {
private:
    static const unsigned int m_width = 16;
    static const unsigned int m_depth = 16;
    static const unsigned int m_height = 256;

    std::vector<uint8_t> m_chunk_contents; // Order of dimensions: XZY
    std::vector<GLfloat> m_chunk_vertices;
    std::vector<GLfloat> m_chunk_uv;
    std::vector<GLfloat> m_chunk_light;
    std::vector<GLushort> m_chunk_indices;

    GLuint m_VAO; // Vertex Array Object
    GLuint m_VBO; // Vertex Buffer Object
    GLuint m_UVBO; // UV Buffer Object
    GLuint m_LBO; // Light Buffer Object
    GLuint m_IDO; // Index Buffer Object

    TextureAtlas * m_texture_atlas; // Handles obtaining uvs for texture atlas and binding during rendering

    float m_xpos;
    float m_ypos;
    float m_zpos;

    template <typename T>
    void pushMany(std::vector<T> &vector, 
                  const T* values, 
                  const unsigned int size, 
                  T offsetX, 
                  T offsetY, 
                  T offsetZ);

    template <typename T>
    void pushMany(std::vector<T> &vector, const T* values, const unsigned int size, int offset);


    template <typename T>
    void pushMany(std::vector<T> &vector, const T* values, const unsigned int size);


    float xposFromIndex(unsigned int i);
    float yposFromIndex(unsigned int i);
    float zposFromIndex(unsigned int i);


    void generateFill();
    void generateFlat(int height);

    void generateMesh();
    void generateCubeMeshData(unsigned int i,
                              unsigned int uv_id_left,
                              unsigned int uv_id_right,
                              unsigned int uv_id_front,
                              unsigned int uv_id_back,
                              unsigned int uv_id_bottom,
                              unsigned int uv_id_top);
    
    void setFaceUV(int id);

public:
    Chunk(GLuint programID, TextureAtlas *texture_atlas, float xpos, float ypos, float zpos);
    ~Chunk();

    void Render(GLuint MVP_handle, glm::mat4 &VP);
};

#endif