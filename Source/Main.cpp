////////////////////////////////////////////////////////////////////////////////
// File:
//
// Description:
//
// Methods:
//
// Fields:
//
// Modification History:
//    Date:        Who:            What:
//  07/25/2019  Tyler Gajewski    Initial Creation
////////////////////////////////////////////////////////////////////////////////

#include "Cube.h"
#include "Application.h"
#include "CameraController.h"
#include "Utils.h"

int main(int argc, char** argv)
{
    spdlog::set_level(spdlog::level::trace);

    // Create the main application window.
    Application application("opengl");

    // Create a camera controller.
    CameraController cameraController;

    // Create an input manager for mouse and keyboard.
    InputManager inputManager;

    // Attach the camera controller to the applcation.
    application.registerCameraController(cameraController);

    // Attach the input manager to the application.
    application.registerInputs(inputManager);

    // Attach the input manager to the camera.
    application.registerInputToCamera(inputManager, cameraController);

    // Create a new Cube to render.
    Cube *cube = new Cube("cube");

    // Create the shader program for the cube.
    ShaderProgram shader(
        "/Users/tyler/Documents/Projects/openglProjects/opengl/Source/Core/Shaders/TransformVertexShader.vertexshader",
        "/Users/tyler/Documents/Projects/openglProjects/opengl/Source/Core/Shaders/ColorFragmentShader.fragmentshader"
    );

    // Attach a shader to the cube.
    cube->useShader(shader);

    // Attach an object to be drawn to the application.
    application.attach(cube);

    application.printVersionInfo();

    // Enter the main application loop.
    application.run();

    return 0;
}
