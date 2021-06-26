#ifndef __SHADER_h_
#define __SHADER_h_
#include <glad/glad.h>
#include <exception>
#include <string>
#include <glm/glm.hpp>

class LoadShaderException: public std::exception {
private:
    const char * msg;
public:
    LoadShaderException(std::string &msg): msg{msg.c_str()} {}
    virtual const char * what() {
        return msg;
    }
};

class Shader {
private:
    GLuint m_programID {0};
    bool m_loaded = false;
public:
    Shader();
    ~Shader();
    void loadShaders(const char * vertex_file_path, const char * fragment_file_path);
    void useProgram();

    GLuint getProgramID();

    // utility functions
    void    setFloat    (const char *name, float value, bool useShader = false);
    void    setInteger  (const char *name, int value, bool useShader = false);
    void    setVector2f (const char *name, float x, float y, bool useShader = false);
    void    setVector2f (const char *name, const glm::vec2 &value, bool useShader = false);
    void    setVector3f (const char *name, float x, float y, float z, bool useShader = false);
    void    setVector3f (const char *name, const glm::vec3 &value, bool useShader = false);
    void    setVector4f (const char *name, float x, float y, float z, float w, bool useShader = false);
    void    setVector4f (const char *name, const glm::vec4 &value, bool useShader = false);
    void    setMatrix4  (const char *name, const glm::mat4 &matrix, bool useShader = false);
};

#endif