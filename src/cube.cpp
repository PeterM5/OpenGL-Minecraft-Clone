#include "cube.h"

Cube::Cube(GLuint programID, TextureAtlas * texture_atlas, unsigned int id, float xpos, float ypos, float zpos)
: m_texture_atlas(texture_atlas)
, m_xpos(xpos)
, m_ypos(ypos)
, m_zpos(zpos)
{
    // VAO
    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

    // VBO
    glGenBuffers(1, &m_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertex_data), cube_vertex_data, GL_STATIC_DRAW);

    // Obtain UVs from texture atlas
    unsigned int length = sizeof(cube_uv_buffer_data)/sizeof(cube_uv_buffer_data[0]);
    GLfloat uvs[length];
    std::copy(cube_uv_buffer_data, cube_uv_buffer_data + length, uvs);
    if (id == 2)
    {
        m_texture_atlas->TransformUV(uvs, 2, 2, 2, 2, 0, 1);
    }
    else
    {
        m_texture_atlas->TransformUV(uvs, length, id);
    }

    // UVBO
    glGenBuffers(1, &m_UVBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_UVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW);

    // LBO (Light Buffer Object)
    glGenBuffers(1, &m_LBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_LBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_light_data), cube_light_data, GL_STATIC_DRAW);


    // Index (Element) Buffer
    glGenBuffers(1, &m_IDO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IDO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices_data), cube_indices_data, GL_STATIC_DRAW);

}

// Move constructor
Cube::Cube(Cube && other) 
    : m_VAO(other.m_VAO)
    , m_VBO(other.m_VBO)
    , m_UVBO(other.m_UVBO)
    , m_LBO(other.m_LBO)
    , m_IDO(other.m_IDO)
    , m_texture_atlas(other.m_texture_atlas)
    , m_xpos(other.m_xpos)
    , m_ypos(other.m_ypos)
    , m_zpos(other.m_zpos)
{
    other.m_VAO = 0;
    other.m_VBO = 0;
    other.m_UVBO = 0;
    other.m_LBO = 0;
    other.m_IDO = 0;
}

Cube::~Cube()
{
    glDeleteBuffers(1, &m_VBO);
    glDeleteBuffers(1, &m_IDO);
    glDeleteBuffers(1, &m_UVBO);
    glDeleteBuffers(1, &m_LBO);
    glDeleteBuffers(1, &m_VAO);
}

void Cube::Render(GLuint MVP_handle, glm::mat4 &VP)
{
    //glBindVertexArray(m_VAO);   

    // Send our transformation to the currently bound shader,
    // in the "MVP" uniform
    glm::mat4 transform = glm::translate<float>(glm::vec3(m_xpos/2, m_ypos/2, m_zpos/2)) 
    * glm::scale<float>(glm::vec3(0.5f,0.5f,0.5f));
    glm::mat4 MVP = VP * transform;
    
    glUniformMatrix4fv(MVP_handle, 1, GL_FALSE, &MVP[0][0]);

    // Bind texture in Texture unit 0 and set our texture sampler to unit 0
    m_texture_atlas->bind();

    // 1rst attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glVertexAttribPointer(
        0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
        3,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        (void*)0            // array buffer offset
    );

    // 2nd attribute buffer : UVs
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, m_UVBO);
    glVertexAttribPointer(
        1,                  // attribute. No particular reason for 0, but must match the layout in the shader.
        2,                  // size: U+V => 2
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        (void*)0            // array buffer offset
    );    

    // 3rd attribute buffer: Light values
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, m_LBO);
    glVertexAttribPointer(
        2,                  // attribute. No particular reason for 0, but must match the layout in the shader.
        1,                  // size: one light values per vertex 
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        (void*)0            // array buffer offset
    );    


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IDO);

    // Draw triangles
    glDrawElements(GL_TRIANGLES, 12*3, GL_UNSIGNED_SHORT, (GLvoid*)0);


    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);

}