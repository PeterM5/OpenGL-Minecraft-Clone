#include "chunk.h"

Chunk::Chunk(GLuint programID, TextureAtlas *texture_atlas, float xpos, float ypos, float zpos)
    :m_texture_atlas(texture_atlas)
    ,m_xpos(xpos)
    ,m_ypos(ypos)
    ,m_zpos(zpos)
{
    // Set memory for chunk
    m_chunk_contents.resize(m_width * m_depth * m_height);

    // Generate chunk block data
    generateFill();

    // Generate mesh data
    generateMesh();
}

Chunk::~Chunk()
{
    glDeleteBuffers(1, &m_VBO);
    glDeleteBuffers(1, &m_IDO);
    glDeleteBuffers(1, &m_UVBO);
    glDeleteBuffers(1, &m_LBO);
    glDeleteBuffers(1, &m_VAO);
}

void Chunk::generateFill()
{
    unsigned int chunk_size = m_width * m_depth * m_height;
    for (unsigned int i = 0; i < m_width * m_depth; i++)
    {
        m_chunk_contents[i] = 3;
    }
    for (unsigned int i = m_width * m_depth; i < chunk_size; i++)
    {
        m_chunk_contents[i] = 1;
    }
}

void Chunk::generateFlat(int height)
{
    unsigned int chunk_size = m_width * m_depth * m_height;
    unsigned int limit = height * m_width * m_depth;
    for (unsigned int i = 0; i < chunk_size; i++)
    {
        if ( i < limit)
            m_chunk_contents[i] = 1;
        else
            m_chunk_contents[i] = 0;
    }
}

void Chunk::generateMesh()
{
    unsigned int chunk_size = m_width * m_depth * m_height;
    for (unsigned int i = 0; i < chunk_size; i++)
    {
        if (m_chunk_contents[i] == 0) {
            // Do nothing
        }
        else if (m_chunk_contents[i] == 3) {
            // Generate vertex/ uv/ light data for cube at index i
            generateCubeMeshData(i, 2, 2, 2, 2, 0, 1);
        }
        else
        {
            generateCubeMeshData(i, m_chunk_contents[i]-1, m_chunk_contents[i]-1, m_chunk_contents[i]-1, m_chunk_contents[i]-1, m_chunk_contents[i]-1, m_chunk_contents[i]-1);
        }
    }
    // VAO
    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

    // VBO
    glGenBuffers(1, &m_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, m_chunk_vertices.size() * sizeof(GLfloat), &m_chunk_vertices[0], GL_STATIC_DRAW);

    // UVBO
    glGenBuffers(1, &m_UVBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_UVBO);
    glBufferData(GL_ARRAY_BUFFER, m_chunk_uv.size() * sizeof(GLfloat), &m_chunk_uv[0], GL_STATIC_DRAW);

    // LBO (Light Buffer Object)
    glGenBuffers(1, &m_LBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_LBO);
    glBufferData(GL_ARRAY_BUFFER, m_chunk_light.size() * sizeof(GLfloat), &m_chunk_light[0], GL_STATIC_DRAW);

    // Index (Element) Buffer
    glGenBuffers(1, &m_IDO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IDO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_chunk_indices.size() * sizeof(GLushort), &m_chunk_indices[0], GL_STATIC_DRAW);

}

void Chunk::setFaceUV(int id)
{
    m_texture_atlas->TransformUV(&m_chunk_uv[m_chunk_uv.size()-8], 8, id);

}

// Generates vertex/ uv/ light data for a cube at index i within the chunk.
// Eg. If a cube is surrounded on all by other cubes, it is hidden so we dont want to render it.
//     If a cube is on the surface of a chunk, we just want to render its top face.
void Chunk::generateCubeMeshData(unsigned int i,
                                 unsigned int uv_id_left,
                                 unsigned int uv_id_right,
                                 unsigned int uv_id_front,
                                 unsigned int uv_id_back,
                                 unsigned int uv_id_bottom,
                                 unsigned int uv_id_top)
{
    // Check adjacent blocks
    if (i % m_width == 0 || m_chunk_contents[i-1] == 0 ) // Left side is open 
    {
        // add vertices
        pushMany(m_chunk_vertices, 
                 cube_vertex_data+24, 
                 12, 
                 xposFromIndex(i),
                 yposFromIndex(i),
                 zposFromIndex(i)
                 );
        // add uv coords
        pushMany(m_chunk_uv, cube_uv_data+16, 8);
        setFaceUV(uv_id_left);
        // add light coords
        pushMany(m_chunk_light, cube_light_data+8, 4);
        // add indices coords
        pushMany(m_chunk_indices, chunk_indices_data+12, 6, m_chunk_vertices.size()/3 - 4);

    }
    if (i % m_width == m_width-1 || m_chunk_contents[i+1] == 0 ) // Right side is open 
    {
        //add vertices
        pushMany(m_chunk_vertices, 
                 cube_vertex_data+36, 
                 12,
                 xposFromIndex(i),
                 yposFromIndex(i),
                 zposFromIndex(i)
                 );
        // add uv coords
        pushMany(m_chunk_uv, cube_uv_data+24, 8);
        setFaceUV(uv_id_right);

        // add light coords
        pushMany(m_chunk_light, cube_light_data+12, 4);
        // add indices coords
        pushMany(m_chunk_indices, chunk_indices_data+18, 6, m_chunk_vertices.size()/3 - 4);
    }
    if ((i % (m_width * m_depth))/m_width == 0 || m_chunk_contents[i-m_width] == 0 ) // Front side is open 
    {
        //add vertices
        pushMany(m_chunk_vertices, 
                 cube_vertex_data, 
                 12,
                 xposFromIndex(i),
                 yposFromIndex(i),
                 zposFromIndex(i)
                 );
        // add uv coords
        pushMany(m_chunk_uv, cube_uv_data, 8);
        setFaceUV(uv_id_front);

        // add light coords
        pushMany(m_chunk_light, cube_light_data, 4);
        // add indices coords
        pushMany(m_chunk_indices, chunk_indices_data, 6, m_chunk_vertices.size()/3 - 4);
    }
    if ((i % (m_width * m_depth))/m_width == m_width-1 || m_chunk_contents[i+m_width] == 0 ) // Back side is open 
    {
        //add vertices
        pushMany(m_chunk_vertices, 
                 cube_vertex_data+12, 
                 12,
                 xposFromIndex(i),
                 yposFromIndex(i),
                 zposFromIndex(i)
                 );
        // add uv coords
        pushMany(m_chunk_uv, cube_uv_data+8, 8);
        setFaceUV(uv_id_back);

        // add light coords
        pushMany(m_chunk_light, cube_light_data+4, 4);
        // add indices coords
        pushMany(m_chunk_indices, chunk_indices_data+6, 6, m_chunk_vertices.size()/3 - 4);
    }
     if (i / (m_width*m_depth) == m_height-1 || m_chunk_contents[i+m_width*m_depth] == 0 ) // Bottom side is open 
    {
        //add vertices
        pushMany(m_chunk_vertices, 
                 cube_vertex_data+48, 
                 12,
                 xposFromIndex(i),
                 yposFromIndex(i),
                 zposFromIndex(i)
                 );
        // add uv coords
        pushMany(m_chunk_uv, cube_uv_data+32, 8);
        setFaceUV(uv_id_bottom);

        // add light coords
        pushMany(m_chunk_light, cube_light_data+16, 4);
        // add indices coords
        pushMany(m_chunk_indices, chunk_indices_data+24, 6, m_chunk_vertices.size()/3 - 4);
    }
    if (i / (m_width*m_depth) == 0 || m_chunk_contents[i-m_width*m_depth] == 0 ) // Top side is open 
    {
        //add vertices
        pushMany(m_chunk_vertices, 
                 cube_vertex_data+60, 
                 12,
                 xposFromIndex(i),
                 yposFromIndex(i),
                 zposFromIndex(i)
                 );
        // add uv coords
        pushMany(m_chunk_uv, cube_uv_data+40, 8);
        setFaceUV(uv_id_top);

        // add light coords
        pushMany(m_chunk_light, cube_light_data+20, 4);
        // add indices coords
        pushMany(m_chunk_indices, chunk_indices_data+30, 6, m_chunk_vertices.size()/3 - 4);
    }

}

template <typename T>
void Chunk::pushMany(std::vector<T> &vector, const T* values, const unsigned int size)
{
    for (unsigned int i=0; i<size; i++)
    {
        vector.push_back(values[i]);
    }
}

// Same as above pushMany() but in this one we also add a scalar offset value
template <typename T>
void Chunk::pushMany(std::vector<T> &vector, const T* values, const unsigned int size, int offset)
{
    for (unsigned int i=0; i<size; i++)
    {
        vector.push_back(values[i] + offset);

    }
}

// Same as above pushMany() but in this one we also add an offset to the location of the inputted
// vertex
template <typename T>
void Chunk::pushMany(std::vector<T> &vector, const T* values, const unsigned int size, T offsetX, T offsetY, T offsetZ)
{
    // Ordering of vertex coords: XYZ
    for (unsigned int i=0; i<size; i++)
    {
        if (i % 3 == 0) // X
        {
            T x = values[i] + offsetX;
            vector.push_back(x);
        }
        else if (i % 3 == 1) // Y
        {
            T y = values[i] + offsetY;
            vector.push_back(y);
        }
       else if (i % 3 == 2)// Z
        {
            T z = values[i] + offsetZ;
            vector.push_back(z);
        }
    }
}

GLfloat Chunk::xposFromIndex(unsigned int i)
{
    return i % m_width;
}

GLfloat Chunk::yposFromIndex(unsigned int i)
{
    return i / (m_width * m_depth);
}

GLfloat Chunk::zposFromIndex(unsigned int i)
{
    return (i % (m_width * m_depth)) / m_width;
}

void Chunk::Render(GLuint MVP_handle, glm::mat4 &VP)
{
    //glBindVertexArray(m_VAO);   

    // Send our transformation to the currently bound shader,
    // in the "MVP" uniform
    glm::mat4 transform = glm::translate<float>(glm::vec3(m_xpos/2, m_ypos/2, m_zpos/2)) 
    * glm::scale<float>(glm::vec3(0.2f,0.2f,0.2f));
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
        1,                  // size: one light value per vertex 
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        (void*)0            // array buffer offset
    );    


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IDO);

    // Draw triangles
    glDrawElements(GL_TRIANGLES, m_chunk_indices.size(), GL_UNSIGNED_SHORT, (GLvoid*)0);


    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);

}