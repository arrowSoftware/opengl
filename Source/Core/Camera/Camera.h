#ifndef _CAMERA_H_
#define _CAMERA_H_

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
        //  SetPosition.
        // Description
        //  Set the position of the camera.
        // Parameters:
        //  argPosition: The position to set the camera to.
        // Returns:
        //  None.
        ////////////////////////////////////////////////////////////////////////
        void SetPosition(glm::vec3 argPosition);

        ////////////////////////////////////////////////////////////////////////
        // Function:
        //  GetPosition.
        // Description
        //  Get the position of the camera.
        // Parameters:
        //  None.
        // Returns:
        //  vec3 of the camera position.
        ////////////////////////////////////////////////////////////////////////
        glm::vec3 GetPosition(void);

        ////////////////////////////////////////////////////////////////////////
        // Function:
        //  GetFacing.
        // Description
        //  This function gets the direction the camera is facing. Anytime the
        //  yaw or pitch is changed, the direction the camera is facing will be
        //  updated.
        // Parameters:
        //  None.
        // Returns:
        //  vec3 of the camera facing position.
        ////////////////////////////////////////////////////////////////////////
        glm::vec3 GetFacing(void);

        ////////////////////////////////////////////////////////////////////////
        // Function:
        //  SetYaw.
        // Description
        //  Set the yaw of the camera.
        // Parameters:
        //  argYaw: Yaw to set.
        // Returns:
        //  None.
        ////////////////////////////////////////////////////////////////////////
        void SetYaw(float argYaw);

        ////////////////////////////////////////////////////////////////////////
        // Function:
        //  GetYaw.
        // Description
        //  Get the yaw of the camera.
        // Parameters:
        //  None.
        // Returns:
        //  Camera yaw.
        ////////////////////////////////////////////////////////////////////////
        float GetYaw(void);

        ////////////////////////////////////////////////////////////////////////
        // Function:
        //  SetPitch.
        // Description
        //  Set the pitch of the camera.
        // Parameters:
        //  argPitch: pitch to set.
        // Returns:
        //  None.
        ////////////////////////////////////////////////////////////////////////
        void SetPitch(float argPitch);

        ////////////////////////////////////////////////////////////////////////
        // Function:
        //  GetPitch.
        // Description
        //  Get the pitch of the camera.
        // Parameters:
        //  Nonne.
        // Returns:
        //  Pitch of the camera.
        ////////////////////////////////////////////////////////////////////////
        float GetPitch(void);

        /// This function returns the view matrix represented by the camera's
        /// position, direction, and up vector.
        ////////////////////////////////////////////////////////////////////////
        // Function:
        //  GetView.
        // Description
        //  This function returns the view matrix represented by the cameras
        //  position, direction and up vector.
        // Parameters:
        //  None.
        // Returns:
        //  View matrix.
        ////////////////////////////////////////////////////////////////////////
        glm::mat4 GetView(void);

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
        //  UpdateFacing.
        // Description
        //  Update where the camera is facing.
        // Parameters:
        //  None.
        // Returns:
        //  None.
        ////////////////////////////////////////////////////////////////////////
        void UpdateFacing(void);

        ////////////////////////////////////////////////////////////////////////
        // Function:
        //  PrintData.
        // Description
        //  Print out the camera, position, direction, yaw and pitch
        // Parameters:
        //  None.
        // Returns:
        //  None.
        ////////////////////////////////////////////////////////////////////////
        void PrintData(void);
};

#endif
