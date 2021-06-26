#ifndef __CONTROLLER_H
#define __CONTROLLER_H

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <sstream>
#include "KeyboardInput.h"


class Controller {
private:
    glm::mat4 m_view_matrix;
    glm::mat4 m_projection_matrix;

    glm::vec3 m_position = glm::vec3(0, 0, 0); // Default camera position is the origin
    // horizontal angle: toward -Z
    double m_horizontal_angle = 3.14f; // in radians
    // verticel angle: 0, look at the hoizon
    double m_vertical_angle = 0.0f; // in radians
    // inital field of view
    double m_initial_fov = 45.0f;

    // camera speed
    double m_speed = 3.0f;
    // mouse sensitivity
    double m_mouse_speed = 0.005f;


public:
    Controller();
    ~Controller();

    void computeMatrices(double delta_time, 
                         double cursor_x_diff,
                         double cursor_y_diff,
                         KeyboardInput keyboard_input
                         );

    glm::mat4 getViewMatrix();
    glm::mat4 getProjectionMatrix();
};

#endif