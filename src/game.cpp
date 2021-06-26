#include "game.h"

Game::Game(unsigned int width, unsigned int height):
m_width{width}, m_height{height}
{
    // Initialise GLFW
    if (!glfwInit())
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        throw GlfwInitException();
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Open a window and create its OpenGL context
    m_window = glfwCreateWindow(width, height, "Version 0.3", NULL, NULL);
    if (m_window == NULL)
    {
        glfwTerminate();
        throw CreateWindowException();
    }
    glfwMakeContextCurrent(m_window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        glfwTerminate();
        throw InitGladException();
    }

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(m_window, GLFW_STICKY_KEYS, GL_TRUE);

    // Dark blue background
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);
    
    // Cull triangles which normal is not towards the camera
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);

    // Hide cursor
    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}

Game::~Game()
{
    glfwTerminate();
}

void Game::Init()
{

    // Create and compile our GLSL program from the shaders
    Shader shader;
    try
    {
        shader.loadShaders("shaders/vertexshader.glsl", "shaders/fragmentshader.glsl");
    }
    catch (LoadShaderException e)
    {
        glfwTerminate();
        throw e;
    }

    // Get a handle for our "MVP" uniform
    GLuint MatrixID = glGetUniformLocation(shader.getProgramID(), "MVP");

    glm::mat4 VP;

    // Initalize Texture Atlas
    TextureAtlas texture_atlas("res/Atlas.bmp", 16, shader.getProgramID());

    // Create quad
    //Texture quad_tex("res/rainbow.bmp", shader.getProgramID());
    PerlinNoise pn(256, 256, 7);

    // Create cubes
    int size = 64;
    std::vector<Cube> cubes;
    cubes.reserve(size*size);
    for (int y=0; y<size; y++) {
        for (int x=0; x<size; x++) {
            float height = floor((pn.getPerlinNoise2D()[y * 256 * 2 + x*2] - pn.getMaxPerlinValue()) * 10 / (pn.getMaxPerlinValue() - pn.getMinPerlinValue()));
            unsigned int item_id = 2;
            cubes.push_back(Cube(shader.getProgramID(), &texture_atlas, item_id, (float)x, height,(float)y));
        }
    }

    Controller controller;

    initTimer();
    do
    {
        // Calculates delta time (time between frames)
        calcDeltaTime();
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        // Use our shader
        shader.useProgram();


        // Handle input from user
        setCursorPos();
        ProcessInput();


        controller.computeMatrices(
            m_delta_time,
            m_cursor_x_diff,
            m_cursor_y_diff,
            m_keyboard_input
        );

        VP = controller.getProjectionMatrix() * controller.getViewMatrix();

        for (int y=0; y<size; y++) {
            for (int x=0; x<size; x++) {
                cubes[y*size + x].Render(MatrixID, VP);
            }
        }

        //quad.Render(MatrixID, VP);

        // Swap buffers
        glfwSwapBuffers(m_window);
        glfwPollEvents();

    } // Check if the ESC key was pressed or the window was closed
    while (glfwGetKey(m_window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
           glfwWindowShouldClose(m_window) == 0);
}

void Game::initTimer() {
    m_last_time = glfwGetTime();
}

void Game::calcDeltaTime() {
    double current_time = glfwGetTime();
    m_delta_time = current_time - m_last_time;
    m_last_time = current_time;
}

void Game::setCursorPos() {
    // Get mouse position
    glfwGetCursorPos(m_window, &m_cursor_x, &m_cursor_y);

    // Reset mouse position for next frame
    glfwSetCursorPos(m_window, m_width/2, m_height/2);

    // Calculate movement of the mouse (how far mouse has moved since last frame)
    m_cursor_x_diff = m_cursor_x - m_width/2;
    m_cursor_y_diff = m_height/2 - m_cursor_y;

}

void Game::ProcessInput()
{
    // Reset all input keys to false
    m_keyboard_input.reset();

    // Move forward
	if (glfwGetKey( m_window, GLFW_KEY_W ) == GLFW_PRESS){
        m_keyboard_input.key_up = true;
	}
	// Move backward
	if (glfwGetKey( m_window, GLFW_KEY_S ) == GLFW_PRESS){
        m_keyboard_input.key_down = true;
	}
	// Strafe right
	if (glfwGetKey( m_window, GLFW_KEY_D ) == GLFW_PRESS){
        m_keyboard_input.key_right = true;
	}
	// Strafe left
	if (glfwGetKey( m_window, GLFW_KEY_A ) == GLFW_PRESS){
        m_keyboard_input.key_left= true;
	}
    // Ascend up
	if (glfwGetKey( m_window, GLFW_KEY_SPACE ) == GLFW_PRESS){
        m_keyboard_input.key_space = true;
	}
    // Descend down 
	if (glfwGetKey( m_window, GLFW_KEY_LEFT_SHIFT ) == GLFW_PRESS
     || glfwGetKey( m_window, GLFW_KEY_RIGHT_SHIFT ) == GLFW_PRESS){
        m_keyboard_input.key_shift = true;
	}

}

void Game::Update(float dt)
{
}

void Game::Render()
{
}
