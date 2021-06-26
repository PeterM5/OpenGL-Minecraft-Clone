#include "controller.h"

Controller::Controller() {

}

Controller::~Controller() {

}

void Controller::computeMatrices(double delta_time, 
                                 double cursor_x_diff,
                                 double cursor_y_diff,
                                 KeyboardInput ki 
                                 ) {
    // Computer new orientation
    m_horizontal_angle += m_mouse_speed * cursor_x_diff;
    m_vertical_angle += m_mouse_speed * cursor_y_diff;

    // Direction: Spherical coordinates to Cartesian coordinates conversion
	// Direction is essentially a front vector
    glm::vec3 direction(
        cos(m_vertical_angle) * sin(m_horizontal_angle),
        sin(m_vertical_angle),
        cos(m_vertical_angle) * cos(m_horizontal_angle)
    );

    // Calculate right vector (vector facing to the right of camera
    glm::vec3 right = glm::vec3(
        sin(m_horizontal_angle - 3.14f/2.0f),
        0,
        cos(m_horizontal_angle - 3.14f/2.0f)
    );

    // Calculate up vector (vector facing above the camera)
    glm::vec3 up = glm::cross(right, direction); // up is perpendicular to right and front

    // Move forward
	if (ki.key_up){
		m_position += direction * (float)delta_time* (float)m_speed;
	}
	// Move backward
	if (ki.key_down){
		m_position -= direction * (float)delta_time * (float)m_speed;
	}
	// Strafe right
	if (ki.key_right){
		m_position += right * (float)delta_time * (float)m_speed;
	}
	// Strafe left
	if (ki.key_left){
		m_position -= right * (float)delta_time * (float)m_speed;
	}
    // Ascend up
	if (ki.key_space){
		m_position += up * (float)delta_time * (float)m_speed;
	}
    // Descend down
	if (ki.key_shift){
		m_position -= up * (float)delta_time * (float)m_speed;
	}

    float FoV = m_initial_fov;

	// Projection matrix : 45� Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	m_projection_matrix = glm::perspective(glm::radians(FoV), 4.0f / 3.0f, 0.1f, 100.0f);
	// Camera matrix
	m_view_matrix = glm::lookAt(
        m_position,           // Camera is here
        m_position+direction, // and looks here : at the same position, plus "direction"
        up                  // Head is up (set to 0,-1,0 to look upside-down)
    );
}

glm::mat4 Controller::getViewMatrix() {
    return m_view_matrix;
}

glm::mat4 Controller::getProjectionMatrix() {
    return m_projection_matrix;
}