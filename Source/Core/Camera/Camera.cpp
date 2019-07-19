#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include "Camera.h"
#include "utils.h"

Camera::Camera(void)
{
    DEBUG_PRINTF("Entry")
    mPosition = glm::vec3(0.0, 0.0, -10.0);
    mYaw = 90.0;
    mPitch = 0.0;
    updateFacing();
}

void Camera::setPosition(glm::vec3 aPosition)
{ DEBUG_PRINTF("Entry")mPosition = aPosition; }

glm::vec3 Camera::getPosition(void)
{ DEBUG_PRINTF("Entry")return mPosition; }

glm::vec3 Camera::getFacing(void)
{ DEBUG_PRINTF("Entry")return mFacing; }

void Camera::setYaw(float aYaw)
{
    DEBUG_PRINTF("Entry")
    mYaw = aYaw;
    updateFacing();
}

float Camera::getYaw(void)
{ DEBUG_PRINTF("Entry")return mYaw; }

void Camera::setPitch(float aPitch)
{
    DEBUG_PRINTF("Entry")
    mPitch = aPitch;
    updateFacing();
}

float Camera::getPitch(void)
{ DEBUG_PRINTF("Entry")return mPitch; }

glm::mat4 Camera::getView(void)
{
    DEBUG_PRINTF("Entry")
    return glm::lookAt(
        mPosition,
        mPosition + mFacing,
        glm::vec3(0.0, 1.0, 0.0));
}

void Camera::updateFacing(void)
{
    DEBUG_PRINTF("Entry")
    mFacing.x = glm::cos(glm::radians(mYaw)) * glm::cos(glm::radians(mPitch));
    mFacing.y = glm::sin(glm::radians(mPitch));
    mFacing.z = glm::sin(glm::radians(mYaw)) * glm::cos(glm::radians(mPitch));
    if (mFacing.x != 0 && mFacing.y != 0 && mFacing.z != 0)
    {
        mFacing = glm::normalize(mFacing);
    }
}

void Camera::printData(void)
{
    DEBUG_PRINTF("Entry")
    std::cout << "Pos: (" << mPosition.x << ", " << mPosition.y << ", " <<
        mPosition.z << ") Dir: (" << mFacing.x << ", " << mFacing.y << ", " <<
        mFacing.z << ") Yaw: " << mYaw << " Pitch: " << mPitch << std::endl;
}
