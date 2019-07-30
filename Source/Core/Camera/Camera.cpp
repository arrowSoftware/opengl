////////////////////////////////////////////////////////////////////////////////
// File:
//    Camera.cpp
// Description:
//
// Methods:
//    See Header.
// Fields:
//    See Header.
// Modification History:
//    Date:        Who:            What:
//  07/25/2019  Tyler Gajewski    Initial Creation
////////////////////////////////////////////////////////////////////////////////

// STL Includes.
#include <iostream>

// OpenGL Includes.
#include <glm/gtc/matrix_transform.hpp>

// Project Includes.
#include "Camera.h"
#include "Utils.h"

Camera::Camera(void) :
    _position(glm::vec3(0.0, 0.0, -10.0)),
    _facing(glm::vec3(0.0, 0.0, 0.0)),
    _yaw(90.0f),
    _pitch(0.0f)
{
    spdlog::trace("{} IN ()", __PRETTY_FUNCTION__);

    // Update the cameras facing orientation.
    updateFacing();

    spdlog::trace("{} OUT ()", __PRETTY_FUNCTION__);
}

void Camera::setPosition(glm::vec3 argPosition)
{
    spdlog::trace("{} IN ({},{},{})",
                  __PRETTY_FUNCTION__,
                  glm::to_string(argPosition));

    // Set the camera position.
    this->_position = argPosition;

    spdlog::trace("{} OUT ()", __PRETTY_FUNCTION__);
}

glm::vec3 Camera::position(void)
{
    spdlog::trace("{} IN ()", __PRETTY_FUNCTION__);
    spdlog::trace("{} OUT ({},{},{})",
                  __PRETTY_FUNCTION__,
                  glm::to_string(this->_position));
    return this->_position;
}

glm::vec3 Camera::facing(void)
{
    spdlog::trace("{} IN ()", __PRETTY_FUNCTION__);
    spdlog::trace("{} OUT ({})",
                  __PRETTY_FUNCTION__,
                  glm::to_string(this->_facing));
    return this->_facing;
}

void Camera::setYaw(float argYaw)
{
    spdlog::trace("{} IN ({})", __PRETTY_FUNCTION__, argYaw);

    // Set the yaw.
    this->_yaw = argYaw;

    // Then update the facing orientation.
    this->updateFacing();

    spdlog::trace("{} OUT ()", __PRETTY_FUNCTION__);
}

float Camera::yaw(void)
{
    spdlog::trace("{} IN ()", __PRETTY_FUNCTION__);
    spdlog::trace("{} OUT ({})", __PRETTY_FUNCTION__, this->_yaw);

    return this->_yaw;
}

void Camera::setPitch(float argPitch)
{
    spdlog::trace("{} IN ({})", __PRETTY_FUNCTION__, argPitch);

    // Set the pitch,
    this->_pitch = argPitch;

    // Then update the facing orientation.
    this->updateFacing();

    spdlog::trace("{} OUT ()", __PRETTY_FUNCTION__);
}

float Camera::pitch(void)
{
    spdlog::trace("{} IN ()", __PRETTY_FUNCTION__);
    spdlog::trace("{} OUT ({})", __PRETTY_FUNCTION__, this->_pitch);

    return this->_pitch;
}

glm::mat4 Camera::view(void)
{
    spdlog::trace("{} IN ()", __PRETTY_FUNCTION__);

    // Get the view.
    glm::mat4 ret = glm::lookAt(
        this->_position,
        this->_position + this->_facing,
        glm::vec3(0.0, 1.0, 0.0));

    spdlog::trace("{} OUT ({})", __PRETTY_FUNCTION__, glm::to_string(ret));
    return ret;
}

void Camera::updateFacing(void)
{
    spdlog::trace("{} IN ()", __PRETTY_FUNCTION__);

    this->_facing.x = glm::cos(glm::radians(this->_yaw)) *
                      glm::cos(glm::radians(this->_pitch));
    this->_facing.y = glm::sin(glm::radians(this->_pitch));
    this->_facing.z = glm::sin(glm::radians(this->_yaw)) *
                      glm::cos(glm::radians(this->_pitch));
    if (this->_facing.x != 0 && this->_facing.y != 0 && this->_facing.z != 0)
    {
        this->_facing = glm::normalize(this->_facing);
    }
    spdlog::trace("{} OUT ({})",
                  __PRETTY_FUNCTION__,
                  glm::to_string(this->_facing));
}

void Camera::printData(void)
{
    std::cout << "Pos: (" << this->_position.x << ", " << this->_position.y << ", " <<
        this->_position.z << ") Dir: (" << this->_facing.x << ", " << this->_facing.y << ", " <<
        this->_facing.z << ") Yaw: " << this->_yaw << " Pitch: " << this->_pitch << std::endl;
}
