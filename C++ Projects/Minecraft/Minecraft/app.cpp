#include "app.h"

#ifdef _DEBUG
#define _GL_DEBUG
#endif

using std::make_shared;
using std::make_unique;

App::App(size_t width, size_t height, bool vsync, bool gl_debug, bool msaa)
    : shaderProgram(), width(width), height(height), vsync(vsync), window(nullptr),
    texture_manager(), camera(), player(), world(), hitray()
{
    if(!glfwInit())
    {
        std::cerr << "GLFW Failed to Initilize" << std::endl;
        throw std::runtime_error("GLFW Failed to Initilize");
    }

    window = glfwCreateWindow(width, height, "Minecraft Vindle Edition", nullptr, nullptr);
    if(!window)
    {
        glfwTerminate();
        std::cerr << "Failed to create GLFW Window" << std::endl;
        throw std::runtime_error("Failed to create GLFW Window");
    }

    glfwSetFramebufferSizeCallback(window, on_resize);
    glfwSetMouseButtonCallback(window, on_mouse_press);
    glfwSetKeyCallback(window, on_key_update);
    glfwSetCursorPosCallback(window, on_cursor_move);

    glfwMakeContextCurrent(window);
    glfwSwapInterval(vsync ? 1 : 0);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Error Initilizing GLAD" << std::endl;
        throw std::runtime_error("Error Initilizing GLAD");
    }

    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << "\n";

    if(gl_debug)
    {
        std::cout << "Enabled OpenGL debugging\n";
        glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback(GLDebugMsgCallback, nullptr);
    }

    if(msaa)
    {
        std::cout << "Enabled multtisampling antiailiasing, expect low performance\n";
        glEnable(GL_MULTISAMPLE);
        glfwWindowHint(GLFW_SAMPLES, 4);
    }
}

void App::init()
{
    std::cout << "Compiling and builing core shaders\n";
    shaderProgram = new ShaderProgram;
    {
        Shader vs("vertex_shader.glsl", GL_VERTEX_SHADER), fs("fragment_shader.glsl", GL_FRAGMENT_SHADER);
        shaderProgram->bindShader(std::move(vs));
        shaderProgram->bindShader(std::move(fs));
    }
    shaderProgram->compile();
    shaderProgram->use();

    std::cout << "Loading textures\n";
    texture_manager = make_shared<TextureManager>(16, 16, shaderProgram);

    std::cout << "Loading and Generating World\n";
    world = new World(texture_manager);

    std::cout << "Initilizing Camera\n";
    player = new Player(glm::vec3(16, 70, 16), 5);
    camera = new Camera(player, shaderProgram, 1280, 720);

    hitray = new PlayerHitray(world);

    link_elements(player, camera, world, hitray);
}

App::~App() noexcept
{
    delete world;
    delete hitray;
    delete player;
    delete camera;
    delete shaderProgram;
}

inline void App::update(float delta_time)
{
    camera->update(delta_time);
    draw();
}

inline void App::draw()
{
    glClearColor(0.4f, 0.7f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
#ifndef _DEBUG
    glEnable(GL_CULL_FACE);
#endif

    world->render();
}

void App::run()
{
    float current_time;
    float prev_time = glfwGetTime();
    float delta_time;
    while(!glfwWindowShouldClose(window))
    {
        current_time = glfwGetTime();
        delta_time = current_time - prev_time;
        std::cout << (int)(1 / delta_time) << " FPS" << std::endl;
        prev_time = current_time;

        update(delta_time);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
}