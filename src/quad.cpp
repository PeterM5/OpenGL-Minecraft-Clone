#include "quad.h"

Quad::Quad(GLuint programID, Texture *texture, float xpos, float ypos, float zpos)
: m_texture(texture)
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
    glBufferData(GL_ARRAY_BUFFER, sizeof(quad_vertex_data), quad_vertex_data, GL_STATIC_DRAW);

    // UVBO
    glGenBuffers(1, &m_UVBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_UVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quad_uv_buffer_data), quad_uv_buffer_data, GL_STATIC_DRAW);

    // Index (Element) Buffer
    glGenBuffers(1, &m_IDO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IDO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(quad_indices_data), quad_indices_data, GL_STATIC_DRAW);

}

// Move constructor
Quad::Quad(Quad && other) 
    : m_VAO(other.m_VAO)
    , m_VBO(other.m_VBO)
    , m_UVBO(other.m_UVBO)
    , m_IDO(other.m_IDO)
    , m_texture(other.m_texture)
    , m_xpos(other.m_xpos)
    , m_ypos(other.m_ypos)
    , m_zpos(other.m_zpos)
{
    other.m_VAO = 0;
    other.m_VBO = 0;
    other.m_UVBO = 0;
    other.m_IDO = 0;
}

Quad::~Quad()
{
    glDeleteBuffers(1, &m_VBO);
    glDeleteBuffers(1, &m_IDO);
    glDeleteBuffers(1, &m_UVBO);
    glDeleteBuffers(1, &m_VAO);
}

void Quad::Render(GLuint MVP_handle, glm::mat4 &VP)
{
    //glBindVertexArray(m_VAO);   

    // Send our transformation to the currently bound shader,
    // in the "MVP" uniform
    glm::mat4 transform = glm::translate<float>(glm::vec3(m_xpos/2, m_ypos/2, m_zpos/2)) 
    * glm::scale<float>(glm::vec3(0.5f,0.5f,0.5f));
    glm::mat4 MVP = VP * transform;
    
    glUniformMatrix4fv(MVP_handle, 1, GL_FALSE, &MVP[0][0]);

    // Bind texture in Texture unit 0 and set our texture sampler to unit 0
    m_texture->bind();

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

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IDO);

    // Draw triangles from indices
    glDrawElements(GL_TRIANGLES, 12*3, GL_UNSIGNED_SHORT, (GLvoid*)0);


    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

}