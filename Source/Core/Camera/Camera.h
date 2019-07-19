#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <glm/glm.hpp>

#include "InputManager.h"

class Camera
{
    public:
        Camera(void);

        void setPosition(glm::vec3 aPosition);
        glm::vec3 getPosition(void);

        /// This function gets the direction the camera is facing. Anytime the yaw
        /// or pitch is changed, the direction the camera is facing will be updated.
        glm::vec3 getFacing(void);
        void setYaw(float aYaw);
        float getYaw(void);
        void setPitch(float aPitch);
        float getPitch(void);

        /// This function returns the view matrix represented by the camera's
        /// position, direction, and up vector.
        glm::mat4 getView(void);

    private:
        // The position of the camera in the world.
        glm::vec3 mPosition;

        // The direction the camera is facing.
        glm::vec3 mFacing;


        // The Yaw of the Camera (Horizontal Rotation)
        float mYaw;

        // the Pitch of the Camera (Vertical Rotation)
        float mPitch;

        void updateFacing(void);
        void printData(void);
};

#endif
