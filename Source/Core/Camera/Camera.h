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
#ifndef SOURCE_CORE_CAMERA_CAMERA_H_
#define SOURCE_CORE_CAMERA_CAMERA_H_

// OpenGL Includes.
#include <glm/glm.hpp>

// Project Includes.
#include "InputManager.h"

class Camera
{
    public:
        ////////////////////////////////////////////////////////////////////////
        // Function:
        //  Camera.
        // Description
        //  Constructor.
        // Parameters:
        //  None.
        // Returns:
        //  Camera object.
        ////////////////////////////////////////////////////////////////////////
        Camera(void);

        ////////////////////////////////////////////////////////////////////////
        // Function:
        //  setPosition.
        // Description
        //  Set the position of the camera.
        // Parameters:
        //  argPosition: The position to set the camera to.
        // Returns:
        //  None.
        ////////////////////////////////////////////////////////////////////////
        void setPosition(glm::vec3 argPosition);

        ////////////////////////////////////////////////////////////////////////
        // Function:
        //  position.
        // Description
        //  Get the position of the camera.
        // Parameters:
        //  None.
        // Returns:
        //  vec3 of the camera position.
        ////////////////////////////////////////////////////////////////////////
        glm::vec3 position(void);

        ////////////////////////////////////////////////////////////////////////
        // Function:
        //  facing.
        // Description
        //  This function gets the direction the camera is facing. Anytime the
        //  yaw or pitch is changed, the direction the camera is facing will be
        //  updated.
        // Parameters:
        //  None.
        // Returns:
        //  vec3 of the camera facing position.
        ////////////////////////////////////////////////////////////////////////
        glm::vec3 facing(void);

        ////////////////////////////////////////////////////////////////////////
        // Function:
        //  setYaw.
        // Description
        //  Set the yaw of the camera.
        // Parameters:
        //  argYaw: Yaw to set.
        // Returns:
        //  None.
        ////////////////////////////////////////////////////////////////////////
        void setYaw(float argYaw);

        ////////////////////////////////////////////////////////////////////////
        // Function:
        //  yaw.
        // Description
        //  Get the yaw of the camera.
        // Parameters:
        //  None.
        // Returns:
        //  Camera yaw.
        ////////////////////////////////////////////////////////////////////////
        float yaw(void);

        ////////////////////////////////////////////////////////////////////////
        // Function:
        //  setPitch.
        // Description
        //  Set the pitch of the camera.
        // Parameters:
        //  argPitch: pitch to set.
        // Returns:
        //  None.
        ////////////////////////////////////////////////////////////////////////
        void setPitch(float argPitch);

        ////////////////////////////////////////////////////////////////////////
        // Function:
        //  pitch.
        // Description
        //  Get the pitch of the camera.
        // Parameters:
        //  Nonne.
        // Returns:
        //  Pitch of the camera.
        ////////////////////////////////////////////////////////////////////////
        float pitch(void);

        ////////////////////////////////////////////////////////////////////////
        // Function:
        //  view.
        // Description
        //  This function returns the view matrix represented by the cameras
        //  position, direction and up vector.
        // Parameters:
        //  None.
        // Returns:
        //  View matrix.
        ////////////////////////////////////////////////////////////////////////
        glm::mat4 view(void);

    private:
        // The position of the camera in the world.
        glm::vec3 _position;

        // The direction the camera is facing.
        glm::vec3 _facing;

        // The Yaw of the Camera (Horizontal Rotation)
        float _yaw;

        // the Pitch of the Camera (Vertical Rotation)
        float _pitch;

        ////////////////////////////////////////////////////////////////////////
        // Function:
        //  updateFacing.
        // Description
        //  Update where the camera is facing.
        // Parameters:
        //  None.
        // Returns:
        //  None.
        ////////////////////////////////////////////////////////////////////////
        void updateFacing(void);

        ////////////////////////////////////////////////////////////////////////
        // Function:
        //  printData.
        // Description
        //  Print out the camera, position, direction, yaw and pitch
        // Parameters:
        //  None.
        // Returns:
        //  None.
        ////////////////////////////////////////////////////////////////////////
        void printData(void);
};

#endif // SOURCE_CORE_CAMERA_CAMERA_H_
