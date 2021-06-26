#include "texture_atlas.h"

TextureAtlas::TextureAtlas(const char * path, unsigned int tile_size, GLuint programID) 
    :m_texture(path, programID)
    ,m_tile_size(tile_size)
{
}

TextureAtlas::~TextureAtlas()
{
}

// Given that uvs is of the format {front, back, left, right, top, bottom}
// this function sets the uvs for a cube for each face
void TextureAtlas::TransformUV(
    GLfloat * uvs, 
    unsigned int id_front,
    unsigned int id_back,
    unsigned int id_left,
    unsigned int id_right,
    unsigned int id_top,
    unsigned int id_bottom)
{
    // Call TransformUV() on all 6 faces
    TransformUV(uvs, 8, id_front);
    TransformUV(uvs+8, 8, id_back);
    TransformUV(uvs+16, 8, id_left);
    TransformUV(uvs+24, 8, id_right);
    TransformUV(uvs+32, 8, id_top);
    TransformUV(uvs+40, 8, id_bottom);
}



// Parameters
//      uvs - A 1D array of uv coords, (each value should be either 0 or 1)
//      id  - ID of texture within atlas
// Returns
//      UV array (same format at uvs) but with uv values set to the location of the texture of id within atlas
void TextureAtlas::TransformUV(GLfloat * uvs, unsigned int length, unsigned int id)
{
    // Calculate lower and upper bounds for texture in atlas
    unsigned int lwr_x = (id % m_texture.getWidth()) * m_tile_size; // x coord lower bound
    unsigned int upr_x = lwr_x + m_tile_size; // x coord upper bound
    unsigned int lwr_y = (id / m_texture.getHeight()) * m_tile_size; // y coord lower bound
    unsigned int upr_y = lwr_y + m_tile_size; // y coord upper bound

    // Calculate uv coord bounds (between 0 and 1)
    GLfloat lwr_U = lwr_x / static_cast<GLfloat>(m_texture.getWidth());
    GLfloat upr_U = upr_x / static_cast<GLfloat>(m_texture.getWidth());
    GLfloat lwr_V = 1.0f - lwr_y / static_cast<GLfloat>(m_texture.getHeight());
    GLfloat upr_V = 1.0f - upr_y / static_cast<GLfloat>(m_texture.getHeight());

    // Calculate new uv values
    for (unsigned int i=0; i<length; i+=2)
    {
        GLfloat u = uvs[i];
        GLfloat v = uvs[i+1];

        // uvs should be an array of floats equal to 0 or 1
        // Incase uvs contains values != 0 or 1 we compare value to 0.5
        if (u < 0.5) // u == 0
        {
            u = lwr_U;
        }
        else // u == 1
        {
            u = upr_U;
        }
        if (v < 0.5) // v == 0
        {
            v = lwr_V;
        }
        else // v == 1
        {
            v = upr_V;
        }

        uvs[i] = u;
        uvs[i+1] = v;
    }
}

void TextureAtlas::bind()
{
    m_texture.bind();
}