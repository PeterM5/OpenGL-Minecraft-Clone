#include "text.h"

Text::Text(GLuint programID, const char * fontpath)
    : m_texture(fontpath, programID)
{
    // Initialize VBO
    glGenBuffers(1, &m_VBO_id);
    glGenBuffers(1, &m_UVBO_id);

    // Initalize Shader
    m_shader_program_id.loadShaders("shaders/TextVertexShader.glsl", "shaders/TextFragmentShader.glsl");

    // Initalize uniform's id
    m_uniform_id = glGetUniformLocation( m_texture.getTextureID(), "myTextureSampler");
}

Text::~Text() {
    // Delete buffers
    glDeleteBuffers(1, &m_VBO_id);
    glDeleteBuffers(1, &m_UVBO_id);
}

void Text::printText(const char * text, int x, int y, int size) {
    unsigned int length = strlen(text);

    // Fill buffers
    std::vector<glm::vec2> vertices;
    std::vector<glm::vec2> UVs;
    // Iterate over each character
    for (unsigned int i=0; i<length; i++) {
        // Compute the coordinates of the four vertices that define quad
        glm::vec2 vertex_up_left    = glm::vec2( x+i*size     , y+size );
        glm::vec2 vertex_up_right   = glm::vec2( x+i*size+size, y+size );
        glm::vec2 vertex_down_right = glm::vec2( x+i*size+size, y      );
        glm::vec2 vertex_down_left  = glm::vec2( x+i*size     , y      );

        // Define two triangles that defines quad
        vertices.push_back(vertex_up_left   );
        vertices.push_back(vertex_down_left );
        vertices.push_back(vertex_up_right  );

        vertices.push_back(vertex_down_right);
        vertices.push_back(vertex_up_right);
        vertices.push_back(vertex_down_left);

        char character = text[i];
        // UV coord is between 0 and 1
        float uv_x = (character%16)/16.0f;
        float uv_y = (character/16)/16.0f;

        // Compute UV coords for four uv vertices that define quad
		glm::vec2 uv_up_left    = glm::vec2( uv_x           , uv_y );
		glm::vec2 uv_up_right   = glm::vec2( uv_x+1.0f/16.0f, uv_y );
		glm::vec2 uv_down_right = glm::vec2( uv_x+1.0f/16.0f, (uv_y + 1.0f/16.0f) );
		glm::vec2 uv_down_left  = glm::vec2( uv_x           , (uv_y + 1.0f/16.0f) );
        // Define two uv triangles that define quad
		UVs.push_back(uv_up_left   );
		UVs.push_back(uv_down_left );
		UVs.push_back(uv_up_right  );

		UVs.push_back(uv_down_right);
		UVs.push_back(uv_up_right);
		UVs.push_back(uv_down_left);
    }

    // Load vertex data
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO_id);
    glBufferData(
        GL_ARRAY_BUFFER, 
        vertices.size() * sizeof(glm::vec2), 
        &vertices[0],
        GL_STATIC_DRAW
    );
    // Load UV data
    glBindBuffer(GL_ARRAY_BUFFER, m_UVBO_id);
    glBufferData(
        GL_ARRAY_BUFFER,
        UVs.size() * sizeof(glm::vec2),
        &UVs[0],
        GL_STATIC_DRAW
    );

    // Bind shader
    m_shader_program_id.useProgram();

    // Bind texture in texture unit 0
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_texture.getTextureID());
    // Set our "myTextureSampler" sampler to user Texture Unit 0
    glUniform1i(m_uniform_id, 0);

    // 1st attribute buffer : vertices (using 2D coords)
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO_id);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

    // 2nd attrib buffer : UVs
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, m_UVBO_id);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Draw call
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());

    glDisable(GL_BLEND);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}