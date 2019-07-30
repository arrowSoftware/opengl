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
// Project Includes.
#include "CameraCommands.h"
#include "Utils.h"

LookCommand::LookCommand(Camera *argCamera, float argYaw, float argPitch)
{
    spdlog::trace("{} IN ({},{},{})",
                  __PRETTY_FUNCTION__,
                  reinterpret_cast<void*>(argCamera),
                  argYaw,
                  argPitch);

    _camera = argCamera;
    _yaw = argYaw;
    _pitch = argPitch;

    spdlog::trace("{} OUT ({})", __PRETTY_FUNCTION__);
}

void LookCommand::execute(void)
{
    spdlog::trace("{} IN ({})", __PRETTY_FUNCTION__);

    this->_camera->setYaw(this->_yaw);
    this->_camera->setPitch(this->_pitch);

    spdlog::trace("{} OUT ({})", __PRETTY_FUNCTION__);
}

MoveCommand::MoveCommand(Camera *argCamera, glm::vec3 argPosition)
{
    spdlog::trace("{} IN ({},{})",
                  __PRETTY_FUNCTION__,
                  reinterpret_cast<void*>(argCamera),
                  glm::to_string(argPosition));

    _camera = argCamera;
    _position = argPosition;

    spdlog::trace("{} OUT ({})", __PRETTY_FUNCTION__);
}

void MoveCommand::execute(void)
{
    spdlog::trace("{} IN ({})", __PRETTY_FUNCTION__);

    this->_camera->setPosition(this->_position);

    spdlog::trace("{} OUT ({})", __PRETTY_FUNCTION__);
}
