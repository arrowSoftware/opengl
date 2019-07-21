// STL Includes.
#include <string>
#include <vector>

// OpenGL Includes.
#include <GL/glew.h>
#include <GLUT/glut.h>
#include <GLFW/glfw3.h>

// Project Includes.
#include "Object.h"
#include "InputManager.h"
#include "CameraController.h"

class Application
{
    public:
        ////////////////////////////////////////////////////////////////////////
        // Function:
        //  Application.
        // Description:
        //  Constructor.
        // Parameters:
        //  argName: String name of the application.
        // Returns:
        //  Application object.
        ////////////////////////////////////////////////////////////////////////
        Application(std::string argName);

        ////////////////////////////////////////////////////////////////////////
        // Function:
        //  ~Application.
        // Description:
        //  Destructor.
        // Parameters:
        //  None.
        // Returns:
        //  None.
        ////////////////////////////////////////////////////////////////////////
        ~Application(void);

        ////////////////////////////////////////////////////////////////////////
        // Function:
        //  Run.
        // Description:
        //  Executes the main application loop.
        // Parameters:
        //  None.
        // Returns:
        //  None.
        ////////////////////////////////////////////////////////////////////////
        void Run(void);

        ////////////////////////////////////////////////////////////////////////
        // Function:
        //  Attach.
        // Description:
        //  Attaches an object to the Application to be drawn.
        // Parameters:
        //  argObj: Object to be drawn.
        // Returns:
        //  None.
        ////////////////////////////////////////////////////////////////////////
        void Attach(Object *arjObj);

        ////////////////////////////////////////////////////////////////////////
        // Function:
        //  Dettach.
        // Description:
        //  Dettaches an object to the Application to be drawn.
        // Parameters:
        //  argObj: Object to be dettached.
        // Returns:
        //  None.
        ////////////////////////////////////////////////////////////////////////
        void Dettach(Object *arjObj);

        ////////////////////////////////////////////////////////////////////////
        // Function:
        //  RegisterInputs.
        // Description:
        //  This function will register an input managers low-level functions
        //  with the applications window.
        // Parameters:
        //  argManager: Input manager.
        // Returns:
        //  None.
        ////////////////////////////////////////////////////////////////////////
        void RegisterInputs(InputManager &argManager);

        ////////////////////////////////////////////////////////////////////////
        // Function:
        //  RegisterCameraController.
        // Description:
        //  This function will register a camera controller with the applcation.
        // Parameters:
        //  argCameraController: camera controller to attach to application.
        // Returns:
        //  None.
        ////////////////////////////////////////////////////////////////////////
        void RegisterCameraController(CameraController &argCameraController);

        ////////////////////////////////////////////////////////////////////////
        // Function:
        //  RegisterInputToCamera.
        // Description:
        //  This function will tie a camera controller to an input manager.
        // Parameters:
        //  argManager: The input manager.
        //  argCameraController: The camera controller.
        // Returns:
        //  None.
        ////////////////////////////////////////////////////////////////////////
        void RegisterInputToCamera(InputManager &argManager,
                                   CameraController &argCameraController);

        ////////////////////////////////////////////////////////////////////////
        // Function:
        //  PrintVersionInfo.
        // Description:
        //  This will print the applcation OpenGL version info.
        // Parameters:
        //  None.
        // Returns:
        //  None.
        ////////////////////////////////////////////////////////////////////////
        void PrintVersionInfo(void);

        ////////////////////////////////////////////////////////////////////////
        // Function:
        //  GetWindow.
        // Description:
        //  Getter for the window pointer.
        // Parameters:
        //  None.
        // Returns:
        //  Returns this objects window pointer.
        ////////////////////////////////////////////////////////////////////////
        GLFWwindow *GetWindow(void);

        ////////////////////////////////////////////////////////////////////////
        // Function:
        //  GetCameraController.
        // Description:
        //  Getter for the camera controller.
        // Parameters:
        //  None.
        // Returns:
        //  Returns this objects camera controller.
        ////////////////////////////////////////////////////////////////////////
        static CameraController GetCameraController(void);

        ////////////////////////////////////////////////////////////////////////
        // Function:
        //  GetName.
        // Description:
        //  Getter for the applications name.
        // Parameters:
        //  None.
        // Returns:
        //  Returns this objects application name.
        ////////////////////////////////////////////////////////////////////////
        std::string GetName(void);

        ////////////////////////////////////////////////////////////////////////
        // Function:
        //  GetInputManager.
        // Description:
        //  Getter for the applications input manager.
        // Parameters:
        //  None.
        // Returns:
        //  Returns this objects input manager.
        ////////////////////////////////////////////////////////////////////////
        static InputManager GetInputManager(void);

    private:
        // This is the applications OpenGL window.
        GLFWwindow *_window;

        // This is the name of the application.
        std::string _name;

        /// Note that the InputManager is static in order to use it for the
        /// callbacks that the GLFW library provides. A side effect means that there
        /// can only be one InputManager.
        static InputManager _inputManager;

        // This is this objects camera controller.
        static CameraController _cameraController;

        // This is a lost of objects to dawn in the main loop.
        std::vector<Object *> _objects;

        ////////////////////////////////////////////////////////////////////////
        // Function:
        //  Draw.
        // Description:
        //  This will draw all attached objects in the main loop.
        // Parameters:
        //  None.
        // Returns:
        //  None.
        ////////////////////////////////////////////////////////////////////////
        void Draw(void);

        ////////////////////////////////////////////////////////////////////////
        // Function:
        //  Wrapup.
        // Description:
        //  This will call all the attached objects wrapup functions.
        // Parameters:
        //  None.
        // Returns:
        //  None.
        ////////////////////////////////////////////////////////////////////////
        void Wrapup(void);

        ////////////////////////////////////////////////////////////////////////
        // Function:
        //  Initialize.
        // Description:
        //  This will call all the attached objects initialize functions.
        // Parameters:
        //  None.
        // Returns:
        //  None.
        ////////////////////////////////////////////////////////////////////////
        void Initialize(void);

        ////////////////////////////////////////////////////////////////////////
        // Function:
        //  KeyCallback.
        // Description:
        //  This will be attached to OpenGLs keyboard callback and will call the
        //  InputManagers keyboard callback
        // Parameters:
        //  argWindow: The OpenGl window with focus.
        //  argKey: Which key was pressed.
        //  argScancode: The scan code of the key.
        //  argAction: Press/Release/Down/Up
        //  argModifiers: Shift/Control/Alt
        // Returns:
        //  None.
        ////////////////////////////////////////////////////////////////////////
        static void KeyCallback(GLFWwindow *argWindow,
                                int argKey,
                                int argScancode,
                                int argAction,
                                int argModifiers);

        ////////////////////////////////////////////////////////////////////////
        // Function:
        //  MouseCallback.
        // Description:
        //  This will be attached to OpenGls mouse callback and will call the
        //  InputManagers mouse callback.
        // Parameters:
        //  argWindow: The OpenGl window with focus.
        //  argXPos: The x position of the mouse.
        //  argYPos: The y position of the mouse.
        // Returns:
        //  None.
        ////////////////////////////////////////////////////////////////////////
        static void MouseCallback(GLFWwindow *arWindow,
                                  double argXpos,
                                  double argYpos);

};
