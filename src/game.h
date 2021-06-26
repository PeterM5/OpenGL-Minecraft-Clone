#ifndef __GAME_H
#define __GAME_H
#include <exception>
#include <vector>
#include <iostream>
#include "shader.cpp"
#include "quad.cpp"
#include "cube.cpp"
#include "controller.cpp"
#include "text.cpp"
#include "KeyboardInput.h"
#include "texture_atlas.cpp"
#include "perlin_noise.cpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class GlfwInitException: public std::exception {
public:
    GlfwInitException() = default;
    virtual const char * what() {
        return "Failed to initalize GLFW";
    }
};

class CreateWindowException: public std::exception {
public:
    CreateWindowException() = default;
    virtual const char * what() {
        return "Failed to create GLFW window.";
    }
};

class InitGladException: public std::exception {
public:
    InitGladException() = default;
    virtual const char * what() {
        return "Failed to initialize GLAD.";
    }
};

// The class that initalizes and runs game funcitons.
class Game
{
private:
    GLFWwindow* m_window;

    // time
    double m_delta_time;
    double m_last_time;
    void initTimer();
    void calcDeltaTime();

    // mouse cursor
    double m_cursor_x, m_cursor_y;
    double m_cursor_x_diff, m_cursor_y_diff; // represents movement of the mouse per frame
    void setCursorPos();

    // get keyboard input
    KeyboardInput m_keyboard_input;
    void ProcessInput();

    unsigned int m_width, m_height;


    // game loop
    void Update(float dt);
    void Render();
public:
    Game(unsigned int width, unsigned int height);
    ~Game();

    // initialize game state (load all shaders/textures/levels)
    void Init();
};

#endif