#include "Cube.h"
#include "Application.h"
#include "CameraController.h"
#include "utils.h"

describe(something, {
	int a, b;
    printf("[%s]\n", __PRETTY_FUNCTION__);
});

int main(int argc, char** argv)
{
    test_something();

    spdlog::set_level(spdlog::level::trace);

    // Create the main application window.
	Application application("opengl");

    // Create a camera controller.
    CameraController cameraController;

    // Create an input manager for mouse and keyboard.
    InputManager inputManager;

    // Attach the camera controller to the applcation.
    application.RegisterCameraController(cameraController);

    // Attach the input manager to the application.
    application.RegisterInputs(inputManager);

    // Attach the input manager to the camera.
    application.RegisterInputToCamera(inputManager, cameraController);

    // Create a new Cube to render.
    Cube *cube = new Cube("cube");

    // Create the shader program for the cube.
    ShaderProgram shader(
        "/Users/tyler/Documents/Projects/openglProjects/opengl/Source/Core/Shaders/TransformVertexShader.vertexshader",
        "/Users/tyler/Documents/Projects/openglProjects/opengl/Source/Core/Shaders/ColorFragmentShader.fragmentshader"
    );

    // Attach a shader to the cube.
    cube->UseShader(shader);

    // Attach an object to be drawn to the application.
    application.Attach(cube);

    application.PrintVersionInfo();

    // Enter the main application loop.
    application.Run();


    return 0;
}
