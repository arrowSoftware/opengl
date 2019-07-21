// Project Includes.
#include "Application.h"
#include "ApplicationException.h"
#include "utils.h"

// STL Includes.
#include <iostream>
#include <algorithm>

// Declare the static members of Application.
InputManager Application::_inputManager;
CameraController Application::_cameraController;

static void ErrorCallback(int error, const char *msg)
{
    std::cerr << "GLFW Error " << error << ": " << msg << std::endl;
}

Application::Application(std::string argName) :
    _window(nullptr),
    _name(argName)
{
    spdlog::trace("{} <- ({})", __PRETTY_FUNCTION__, argName);

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

    spdlog::trace("{} -> ()", __PRETTY_FUNCTION__);
}

Application::~Application(void)
{
    spdlog::trace("{} <- ()", __PRETTY_FUNCTION__);

    // Destruct the window
    glfwDestroyWindow(_window);

    // Terminate GLFW
    glfwTerminate();

    // Clean up members.
    _window = nullptr;
    _name = "";
    _objects.clear();

    spdlog::trace("{} -> ()", __PRETTY_FUNCTION__);
}

void Application::Run(void)
{
    spdlog::trace("{} <- ()", __PRETTY_FUNCTION__);

    // Enable depth test
    glEnable(GL_DEPTH_TEST);

    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);

    // Set the baclgroud color to blue.
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    // Enable sticky keys for the window.
    glfwSetInputMode(_window, GLFW_STICKY_KEYS, GL_TRUE);

    // Initialize all objects.
    this->Initialize();

    // Enter main loop.
    spdlog::trace("{} Entering main loop", __PRETTY_FUNCTION__);

    // Stay in the loop until the escape key is hit or the window is supposed to
    // close.
    do
    {
        // Draw all attached objects.
        this->Draw();

        // Poll for mouse/keyboard events.
        glfwPollEvents();
    } while (glfwGetKey(this->_window, GLFW_KEY_ESCAPE) !=
             GLFW_PRESS && glfwWindowShouldClose(this->_window) == 0);

    spdlog::trace("{} Exiting main loop", __PRETTY_FUNCTION__);

    // Wrapup all attached objects.
    this->Wrapup();

    spdlog::trace("{} -> ()", __PRETTY_FUNCTION__);
}

void Application::Attach(Object *argObject)
{
    spdlog::trace("{} <- ({})", __PRETTY_FUNCTION__, argObject->GetObjectName());

    // Add object to the draw list.
    this->_objects.push_back(argObject);

    spdlog::trace("{} -> ()", __PRETTY_FUNCTION__);
}

void Application::Dettach(Object *argObject)
{
    spdlog::trace("{} <- ({})", __PRETTY_FUNCTION__, argObject->GetObjectName());

    std::vector<Object *>::iterator it = std::find(
        this->_objects.begin(),
        this->_objects.end(),
        argObject);

    if (this->_objects.end() != it)
    {
        this->_objects.erase(it);
        spdlog::debug("{} Erased: {}", __PRETTY_FUNCTION__, argObject->GetObjectName());
    }

    spdlog::trace("{} -> ()", __PRETTY_FUNCTION__);

}

void Application::RegisterInputs(InputManager &argManager)
{
    spdlog::trace("{} -> ({})", __PRETTY_FUNCTION__, (void*)&argManager);

    Application::_inputManager = argManager;

    glfwSetKeyCallback(this->_window, Application::KeyCallback);
    glfwSetInputMode(this->_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(this->_window, Application::MouseCallback);

    spdlog::trace("{} <- ()", __PRETTY_FUNCTION__);
}

void Application::RegisterCameraController(CameraController &argCameraController)
{
    spdlog::trace("{} -> ({})",
                  __PRETTY_FUNCTION__,
                  (void*)&argCameraController);

    Application::_cameraController = argCameraController;

    spdlog::trace("{} <- ()", __PRETTY_FUNCTION__);
}

void Application::RegisterInputToCamera(InputManager &argManager,
                                        CameraController &argCameraController)
{
    spdlog::trace("{} -> ({},{})",
                  __PRETTY_FUNCTION__,
                  (void*)&argManager,
                  (void*)&argCameraController);

    argCameraController.registerWith(argManager);

    spdlog::trace("{} <- ()", __PRETTY_FUNCTION__);
}

void Application::PrintVersionInfo(void)
{
    spdlog::trace("{} <- ()", __PRETTY_FUNCTION__);

    int major, minor, revision;

    glfwGetVersion(&major, &minor, &revision);
    std::cout << "GLFW Version "
        << major << "." << minor << "." << revision << std::endl;

    std::cout << "OpenGL Version " << glGetString(GL_VERSION) << std::endl;

    std::cout << "GLM Version " << GLM_VERSION_MAJOR << "." << GLM_VERSION_MINOR
        << "." << GLM_VERSION_PATCH << "." << GLM_VERSION_REVISION << std::endl;

    spdlog::trace("{} -> ()", __PRETTY_FUNCTION__);
}

GLFWwindow *Application::GetWindow(void)
{
    spdlog::trace("{} <- ()", __PRETTY_FUNCTION__);
    spdlog::trace("{} -> ({})", __PRETTY_FUNCTION__, (void*)this->_window);
    return this->_window;
}

CameraController Application::GetCameraController(void)
{
    spdlog::trace("{} <- ()", __PRETTY_FUNCTION__);
    spdlog::trace("{} -> ({})",
                  __PRETTY_FUNCTION__,
                  (void*)&Application::_cameraController);
    return Application::_cameraController;
}

std::string Application::GetName(void)
{
    spdlog::trace("{} <- ()", __PRETTY_FUNCTION__);
    spdlog::trace("{} -> ({})", __PRETTY_FUNCTION__, this->_name);
    return this->_name;
}

InputManager Application::GetInputManager(void)
{
    spdlog::trace("{} <- ()", __PRETTY_FUNCTION__);
    spdlog::trace("{} -> ({})",
                  __PRETTY_FUNCTION__,
                  (void*)&Application::_inputManager);
    return Application::_inputManager;
}

void Application::Draw(void)
{
    spdlog::trace("{} -> ()", __PRETTY_FUNCTION__);

    // Get the window buffer size.
    GLint width, height;
    glfwGetFramebufferSize(this->_window, &width, &height);

    // Set the view port.
    glViewport(0, 0, width, height);

    // Set the background.
    glClearColor(0.0, 0.0, 4.0, 1.0);

    // Clear the screen.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Draw each attached object.
    for (Object *object : this->_objects)
    {
        object->Draw();
    }

    // swap front and back buffers.
    glfwSwapBuffers(this->_window);
    spdlog::trace("{} <- ()", __PRETTY_FUNCTION__);
}

void Application::Wrapup(void)
{
    spdlog::trace("{} -> ()", __PRETTY_FUNCTION__);

    // wrapup and delete all attached objects.
    for (Object *object : this->_objects)
    {
        object->Wrapup();
        delete object;
    }
    spdlog::trace("{} <- ()", __PRETTY_FUNCTION__);
}

void Application::Initialize(void)
{
    spdlog::trace("{} -> ()", __PRETTY_FUNCTION__);

    // Initialize all attached objects.
    for (Object *object : this->_objects)
    {
        object->Initialize();
    }
    spdlog::trace("{} <- ()", __PRETTY_FUNCTION__);
}

void Application::KeyCallback(GLFWwindow *window, int key, int scancode,
    int action, int modifiers)
{
    spdlog::trace("{} -> ()", __PRETTY_FUNCTION__);

    // Call the inputs managers keyboard callback.
    Application::_inputManager.KeyCallback(window, key, scancode, action, modifiers);
    spdlog::trace("{} <- ()", __PRETTY_FUNCTION__);
}

void Application::MouseCallback(GLFWwindow *window, double xpos, double ypos)
{
    spdlog::trace("{} -> ()", __PRETTY_FUNCTION__);

    // call the input managers mouse callback.
    Application::_inputManager.MouseCallback(window, xpos, ypos);
    spdlog::trace("{} <- ()", __PRETTY_FUNCTION__);
}
