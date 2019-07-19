#include "Application.h"
#include "ApplicationException.h"
#include "utils.h"
#include <chrono>
#include <iostream>
#include <thread>

InputManager Application::mInputManager;
CameraController Application::mCameraController;

static void ErrorCallback(int error, const char *msg)
{
    DEBUG_PRINTF("Entry")
    std::cerr << "GLFW Error " << error << ": " << msg << std::endl;
}

Application::Application(std::string argName) :
    _name(argName)
{
    DEBUG_PRINTF("Entry")
    // Initialise GLFW
    if (!glfwInit())
    {
        throw ApplicationException("GLFW Initialization Failure");
    }

    // Set the error callback
    glfwSetErrorCallback(ErrorCallback);

    glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Open a window and create its OpenGL context
	_window = glfwCreateWindow(1024, 768, argName.c_str(), NULL, NULL);
	if (NULL == _window)
    {
        throw ApplicationException("Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible.  Try 2.1");
	}

    // Make the window's context current
    glfwMakeContextCurrent(_window);

    // Initialize GLEW
	if (GLEW_OK != glewInit())
    {
        throw ApplicationException("Failed to initialize GLEW");
	}
}

Application::~Application(void)
{
    DEBUG_PRINTF("Entry")
    // Destruct the window
    glfwDestroyWindow(_window);

    // Terminate GLFW
    glfwTerminate();
}

void Application::Run(void)
{
    // Enable depth test
    glEnable(GL_DEPTH_TEST);

    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);

    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    glfwSetInputMode(_window, GLFW_STICKY_KEYS, GL_TRUE);

    this->Initialize();

    do
    {
        this->Draw();
        glfwPollEvents();
    } while (glfwGetKey(_window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(_window) == 0);

    this->Wrapup();

    /*
    DEBUG_PRINTF("Entry")
    double curTime, updateTime;
    const double delta = 1.0/60.0;
    unsigned int skipFrames = 0;

    // Configure OpenGL
    glEnable(GL_DEPTH_TEST);

    this->Initialize();

    // The main loop
    std::cout << "Beginning Main Loop ..." << std::endl;
    updateTime = glfwGetTime();
    while (!glfwWindowShouldClose(_window))
    {
        curTime = glfwGetTime();
        if (curTime >= updateTime)
        {
            updateTime += delta;
            if ((curTime < updateTime) || (skipFrames > 10))
            {
                this->Draw();
                skipFrames = 0;
            }
            else
            {
                skipFrames++;
            }
        }
        else
        {
            // Try to sleep for the remainder of the frame in order to reduce
            // CPU usage.
            int ms = (updateTime - curTime) * 1000;
            if (ms > 0)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(ms));
            }
        }
    }
    std::cout << "Exiting Main Loop ..." << std::endl;
    this->Wrapup();
    */
}

GLFWwindow *Application::Window(void)
{
    DEBUG_PRINTF("Entry")
    return this->_window;
}

void Application::AddObject(Object *argObject)
{
    DEBUG_PRINTF("Entry")
    this->_objects.push_back(argObject);
}

void Application::printVersionInfo(void)
{
    int major, minor, revision;

    glfwGetVersion(&major, &minor, &revision);
    std::cout << "GLFW Version "
        << major << "." << minor << "." << revision << std::endl;

    std::cout << "OpenGL Version " << glGetString(GL_VERSION) << std::endl;

    std::cout << "GLM Version " << GLM_VERSION_MAJOR << "." << GLM_VERSION_MINOR
        << "." << GLM_VERSION_PATCH << "." << GLM_VERSION_REVISION << std::endl;
}

void Application::RegisterInputs(InputManager &manager)
{
    DEBUG_PRINTF("Entry")
    mInputManager = manager;

    glfwSetKeyCallback(this->_window, KeyCallback);
    glfwSetInputMode(this->_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(this->_window, MouseCallback);
}

void Application::RegisterCameraController(CameraController &cameraController)
{
    DEBUG_PRINTF("Entry")
    mCameraController = cameraController;
}

void Application::RegisterInputToCamera(InputManager &manager, CameraController &cameraController)
{
    DEBUG_PRINTF("Entry")
    cameraController.registerWith(manager);
}

void Application::Draw(void)
{
    DEBUG_PRINTF("Entry")
    GLint width, height;

    glfwGetFramebufferSize(this->_window, &width, &height);
    glViewport(0, 0, width, height);
    glClearColor(0.0, 0.0, 4.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Perform RenderInterface Rendering
    for (Object *object : this->_objects)
    {
        object->Draw();
    }

    glfwSwapBuffers(this->_window);
}

void Application::Initialize(void)
{
    DEBUG_PRINTF("Entry")
    for (Object *object : this->_objects)
    {
        object->Initialize();
    }
}

void Application::Wrapup(void)
{
    DEBUG_PRINTF("Entry")
    for (Object *object : this->_objects)
    {
        object->Wrapup();
        delete object;
    }
}

void Application::KeyCallback(GLFWwindow *window, int key, int scancode,
    int action, int modifiers)
{
    DEBUG_PRINTF("Entry")
    mInputManager.KeyCallback(window, key, scancode, action, modifiers);
}

void Application::MouseCallback(GLFWwindow *window, double xpos, double ypos)
{
    DEBUG_PRINTF("Entry")
    mInputManager.MouseCallback(window, xpos, ypos);
}
