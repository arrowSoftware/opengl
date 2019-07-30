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
////////////////////////////////////////////////////////////////////////////////
/// This file contains several command classes that the Camera responds to. Most
/// of these commands are generated and responded to by the InputManager.
////////////////////////////////////////////////////////////////////////////////
#ifndef SOURCE_CORE_COMMANDS_CAMERACOMMANDS_H_
#define SOURCE_CORE_COMMANDS_CAMERACOMMANDS_H_

// OpenGL Includes.
#include <glm/glm.hpp>

// Project Includes.
#include "Camera.h"
#include "Command.h"

class LookCommand : public Command
{
    public:
        ////////////////////////////////////////////////////////////////////////
        // Function:
        //  LookCommand.
        // Description:
        //  A command to cause the camera to look at a spcific point.
        // Parameters:
        //  argCamera: The camera instance.
        //  argYaw: Yaw of the camera.
        //  argPitch: Pitch of the camera.
        // Returns:
        //  LookCommand object.
        ////////////////////////////////////////////////////////////////////////
        LookCommand(Camera *argCamera, float argYaw, float argPitch);

        ////////////////////////////////////////////////////////////////////////
        // Function:
        //  execute.
        // Description:
        //  Executes the command.
        // Parameters:
        //  None.
        // Returns:
        //  None.
        ////////////////////////////////////////////////////////////////////////
        virtual void execute(void);

    private:
        // The camera object.
        Camera *_camera;

        // Yaw to set.
        float _yaw;

        // pitch to set.
        float _pitch;
};

class MoveCommand : public Command
{
    public:
        ////////////////////////////////////////////////////////////////////////
        // Function:
        //  MoveCommand.
        // Description:
        //  A command to cause the camera to move to a spcific location.
        // Parameters:
        //  argCamera: The camera to move.
        //  argPosition: The position to move to.
        // Returns:
        //  MoveCommand object.
        ////////////////////////////////////////////////////////////////////////
        MoveCommand(Camera *argCamera, glm::vec3 argPosition);

        ////////////////////////////////////////////////////////////////////////
        // Function:
        //  execute.
        // Description:
        //  Executes the command.
        // Parameters:
        //  None.
        // Returns:
        //  None.
        ////////////////////////////////////////////////////////////////////////
        virtual void execute(void);

    private:
        // The camera object.
        Camera *_camera;

        // Position to move to.
        glm::vec3 _position;
};

#endif // SOURCE_CORE_COMMANDS_CAMERACOMMANDS_H_
