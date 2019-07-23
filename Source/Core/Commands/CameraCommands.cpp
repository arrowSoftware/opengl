// Project Includes.
#include "CameraCommands.h"
#include "Utils.h"

LookCommand::LookCommand(Camera *argCamera, float argYaw, float argPitch)
{
    spdlog::trace("{} IN ({},{},{})",
                  __PRETTY_FUNCTION__,
                  (void*)argCamera,
                  argYaw,
                  argPitch);

    _camera = argCamera;
    _yaw = argYaw;
    _pitch = argPitch;

    spdlog::trace("{} OUT ({})", __PRETTY_FUNCTION__);
}

void LookCommand::Execute(void)
{
    spdlog::trace("{} IN ({})", __PRETTY_FUNCTION__);

    this->_camera->SetYaw(this->_yaw);
    this->_camera->SetPitch(this->_pitch);

    spdlog::trace("{} OUT ({})", __PRETTY_FUNCTION__);
}

MoveCommand::MoveCommand(Camera *argCamera, glm::vec3 argPosition)
{
    spdlog::trace("{} IN ({},{})",
                  __PRETTY_FUNCTION__,
                  (void*)argCamera,
                  glm::to_string(argPosition));

    _camera = argCamera;
    _position = argPosition;

    spdlog::trace("{} OUT ({})", __PRETTY_FUNCTION__);
}

void MoveCommand::Execute(void)
{
    spdlog::trace("{} IN ({})", __PRETTY_FUNCTION__);

    this->_camera->SetPosition(this->_position);

    spdlog::trace("{} OUT ({})", __PRETTY_FUNCTION__);
}
