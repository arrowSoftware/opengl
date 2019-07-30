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
#ifndef _APPLICATION_H_
#define _APPLICATION_H_

// STL Includes.
#include <string>
#include <vector>

// OpenGL Includes.
#include <GL/glew.h>
#ifdef _OSX_
#include <GLUT/glut.h>
#else // _WINDOWS_, _LINUX_
#include <GL/glut.h>
#endif // OSX
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
        //  run.
        // Description:
        //  Executes the main application loop.
        // Parameters:
        //  None.
        // Returns:
        //  None.
        ////////////////////////////////////////////////////////////////////////
        void run(void);

        ////////////////////////////////////////////////////////////////////////
        // Function:
        //  attach.
        // Description:
        //  Attaches an object to the Application to be drawn.
        // Parameters:
        //  argObj: Object to be drawn.
        // Returns:
        //  None.
        ////////////////////////////////////////////////////////////////////////
        void attach(Object *arjObj);

        ////////////////////////////////////////////////////////////////////////
        // Function:
        //  dettach.
        // Description:
        //  Dettaches an object to the Application to be drawn.
        // Parameters:
        //  argObj: Object to be dettached.
        // Returns:
        //  None.
        ////////////////////////////////////////////////////////////////////////
        void dettach(Object *arjObj);

        ////////////////////////////////////////////////////////////////////////
        // Function:
        //  registerInputs.
        // Description:
        //  This function will register an input managers low-level functions
        //  with the applications window.
        // Parameters:
        //  argManager: Input manager.
        // Returns:
        //  None.
        ////////////////////////////////////////////////////////////////////////
        void registerInputs(InputManager &argManager);

        ////////////////////////////////////////////////////////////////////////
        // Function:
        //  registerCameraController.
        // Description:
        //  This function will register a camera controller with the applcation.
        // Parameters:
        //  argCameraController: camera controller to attach to application.
        // Returns:
        //  None.
        ////////////////////////////////////////////////////////////////////////
        void registerCameraController(CameraController &argCameraController);

        ////////////////////////////////////////////////////////////////////////
        // Function:
        //  registerInputToCamera.
        // Description:
        //  This function will tie a camera controller to an input manager.
        // Parameters:
        //  argManager: The input manager.
        //  argCameraController: The camera controller.
        // Returns:
        //  None.
        ////////////////////////////////////////////////////////////////////////
        void registerInputToCamera(InputManager &argManager,
                                   CameraController &argCameraController);

        ////////////////////////////////////////////////////////////////////////
        // Function:
        //  printVersionInfo.
        // Description:
        //  This will print the applcation OpenGL version info.
        // Parameters:
        //  None.
        // Returns:
        //  None.
        ////////////////////////////////////////////////////////////////////////
        void printVersionInfo(void);

        ////////////////////////////////////////////////////////////////////////
        // Function:
        //  window.
        // Description:
        //  Getter for the window pointer.
        // Parameters:
        //  None.
        // Returns:
        //  Returns this objects window pointer.
        ////////////////////////////////////////////////////////////////////////
        GLFWwindow *window(void);

        ////////////////////////////////////////////////////////////////////////
        // Function:
        //  cameraController.
        // Description:
        //  Getter for the camera controller.
        // Parameters:
        //  None.
        // Returns:
        //  Returns this objects camera controller.
        ////////////////////////////////////////////////////////////////////////
        static CameraController cameraController(void);

        ////////////////////////////////////////////////////////////////////////
        // Function:
        //  name.
        // Description:
        //  Getter for the applications name.
        // Parameters:
        //  None.
        // Returns:
        //  Returns this objects application name.
        ////////////////////////////////////////////////////////////////////////
        std::string name(void);

        ////////////////////////////////////////////////////////////////////////
        // Function:
        //  inputManager.
        // Description:
        //  Getter for the applications input manager.
        // Parameters:
        //  None.
        // Returns:
        //  Returns this objects input manager.
        ////////////////////////////////////////////////////////////////////////
        static InputManager inputManager(void);

    private:
        // This is the applications OpenGL window.
        GLFWwindow *_window;

        // This is the name of the application.
        std::string _name;

        // Note that the InputManager is static in order to use it for the
        // callbacks that the GLFW library provides. A side effect means that
        // there  can only be one InputManager.
        static InputManager _inputManager;

        // This is this objects camera controller.
        static CameraController _cameraController;

        // This is a lost of objects to be drawn in the main loop.
        std::vector<Object *> _objects;

        ////////////////////////////////////////////////////////////////////////
        // Function:
        //  draw.
        // Description:
        //  This will draw all attached objects in the main loop.
        // Parameters:
        //  None.
        // Returns:
        //  None.
        ////////////////////////////////////////////////////////////////////////
        void draw(void);

        ////////////////////////////////////////////////////////////////////////
        // Function:
        //  wrapup.
        // Description:
        //  This will call all the attached objects wrapup functions.
        // Parameters:
        //  None.
        // Returns:
        //  None.
        ////////////////////////////////////////////////////////////////////////
        void wrapup(void);

        ////////////////////////////////////////////////////////////////////////
        // Function:
        //  initialize.
        // Description:
        //  This will call all the attached objects initialize functions.
        // Parameters:
        //  None.
        // Returns:
        //  None.
        ////////////////////////////////////////////////////////////////////////
        void initialize(void);

        ////////////////////////////////////////////////////////////////////////
        // Function:
        //  keyCallback.
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
        static void keyCallback(GLFWwindow *argWindow,
                                int argKey,
                                int argScancode,
                                int argAction,
                                int argModifiers);

        ////////////////////////////////////////////////////////////////////////
        // Function:
        //  mouseCallback.
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
        static void mouseCallback(GLFWwindow *arWindow,
                                  float argXpos,
                                  float argYpos);
};

#endif // _APPLICATION_H_
