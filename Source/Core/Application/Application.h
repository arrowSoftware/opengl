#include <string>
#include <vector>

#include <GL/glew.h>
#include <GLUT/glut.h>
#include <GLFW/glfw3.h>

#include "Object.h"
#include "InputManager.h"
#include "CameraController.h"

class Application
{
    public:
        Application(std::string argName);
        ~Application(void);

        void Run(void);

        GLFWwindow *Window(void);

        void AddObject(Object *arjObj);

        /// This function will register an input manager's low-level functions with
        /// the application's window.
        void RegisterInputs(InputManager &manager);
        void RegisterCameraController(CameraController &cameraController);
        void RegisterInputToCamera(InputManager &manager, CameraController &cameraController);
        void printVersionInfo(void);
        static CameraController mCameraController;

    private:
        GLFWwindow *_window;
        std::string _name;
        std::vector<Object *> _objects;

        /// Note that the InputManager is static in order to use it for the
        /// callbacks that the GLFW library provides. A side effect means that there
        /// can only be one InputManager.
        static InputManager mInputManager;

        void Draw(void);
        void Wrapup(void);
        void Initialize(void);

        static void KeyCallback(GLFWwindow *window,
                                int key,
                                int scancode,
                                int action,
                                int modifiers);
        static void MouseCallback(GLFWwindow *window,
                                  double xpos,
                                  double ypos);

};
