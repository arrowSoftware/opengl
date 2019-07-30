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

// STL Includes.
#include <iostream>

// Project Includes.
#include "CameraCommands.h"
#include "InputManager.h"
#include "CameraController.h"
#include "Utils.h"

// This represents a vector UP orientation.
static const glm::vec3 VECTOR_UP = glm::vec3(0.0, 1.0, 0.0);

// This is the "camera" movement speed.
static const float MOVEMENT_SPEED = 0.5f;

// This is the cameras look speed, or mouse speed.
static const float LOOK_SPEED = 0.25f;

CameraController::CameraController(void)
{
    spdlog::trace("{} IN ()", __PRETTY_FUNCTION__);

    // set the event states to the initial max size.
    _eventStates.resize(ApplicationEventEnum::AE_MAX_EVENT_ENUM);

    spdlog::trace("{} OUT ()", __PRETTY_FUNCTION__);
}

void CameraController::registerWith(InputManager &argManager)
{
    spdlog::trace("{} IN ()", __PRETTY_FUNCTION__);

    // Register to be notified for the following events.
    argManager.registerInput(ApplicationEventEnum::AE_MOVE_FORWARD, this);
    argManager.registerInput(ApplicationEventEnum::AE_MOVE_BACKWARD, this);
    argManager.registerInput(ApplicationEventEnum::AE_MOVE_LEFT, this);
    argManager.registerInput(ApplicationEventEnum::AE_MOVE_RIGHT, this);
    argManager.registerInput(ApplicationEventEnum::AE_MOVE_UP, this);
    argManager.registerInput(ApplicationEventEnum::AE_MOVE_DOWN, this);
    argManager.registerInput(ApplicationEventEnum::AE_LOOK_AROUND, this);

    spdlog::trace("{} OUT ()", __PRETTY_FUNCTION__);
}

void CameraController::onEvent(ApplicationEventStruct argEvent)
{
    spdlog::trace("{} IN ()", __PRETTY_FUNCTION__);

    // If this is not a repeating event than store the type in this objects
    // Event list.
    if (argEvent.type != ApplicationEventType::AE_REPEAT)
    {
        this->_eventStates[argEvent.code] = argEvent.type;
    }

    // Process the event.
    switch (argEvent.code)
    {
        // Process mouse/camera look movement.
        case ApplicationEventEnum::AE_LOOK_AROUND:
            // Get the mouse data.
            this->_cursorData = argEvent.data;
            break;

        default:
            break;
    }

    spdlog::trace("{} OUT ()", __PRETTY_FUNCTION__);
}

void CameraController::update(void)
{
    spdlog::trace("{} IN ()", __PRETTY_FUNCTION__);

    // Update camera position.
    this->updatePosition();

    // Update camera facing orientation.
    this->updateFacing();

    spdlog::trace("{} OUT ()", __PRETTY_FUNCTION__);
}

glm::mat4 CameraController::view(void)
{
    spdlog::trace("{} IN ()", __PRETTY_FUNCTION__);
    spdlog::trace("{} OUT ()", __PRETTY_FUNCTION__);

    return this->_camera.view();
}

glm::vec3 CameraController::position(void)
{
    spdlog::trace("{} IN ()", __PRETTY_FUNCTION__);

    // Get the camera position for return/log.
    glm::vec3 ret = this->_camera.position();

    spdlog::trace("{} OUT ({})", __PRETTY_FUNCTION__, glm::to_string(ret));

    return ret;
}

void CameraController::updatePosition(void)
{
    spdlog::trace("{} IN ()", __PRETTY_FUNCTION__);

    glm::vec3 position = this->_camera.position();
    glm::vec3 direction = this->_camera.facing();
    glm::vec3 deltaPos = glm::vec3(0);

    Command *cmd;

    // Calculate the new position of the Camera based upon which events have
    // been received.
    if (this->_eventStates[AE_MOVE_BACKWARD] == AE_BEGIN)
    {
        deltaPos -= direction;
    }
    if (this->_eventStates[AE_MOVE_FORWARD] == AE_BEGIN)
    {
        deltaPos += direction;
    }
    if (this->_eventStates[AE_MOVE_LEFT] == AE_BEGIN)
    {
        deltaPos -= glm::normalize(glm::cross(
                direction,
                VECTOR_UP));
    }
    if (this->_eventStates[AE_MOVE_RIGHT] == AE_BEGIN)
    {
        deltaPos += glm::normalize(glm::cross(
                direction,
                VECTOR_UP));
    }
    if (this->_eventStates[AE_MOVE_UP] == AE_BEGIN)
    {
        deltaPos += VECTOR_UP;
    }
    if (this->_eventStates[AE_MOVE_DOWN] == AE_BEGIN)
    {
        deltaPos -= VECTOR_UP;
    }

    // deltaPos contains the new location to move to. In order to control the
    // movement speed, normalize the difference between the current and new
    // position.
    if (deltaPos != glm::vec3(0))
    {
        deltaPos = glm::normalize(deltaPos) * MOVEMENT_SPEED;
    }

    // Create the command.
    cmd = new MoveCommand(&this->_camera, position + deltaPos);
    cmd->execute();
    delete cmd;

    spdlog::trace("{} OUT ()", __PRETTY_FUNCTION__);
}

void CameraController::updateFacing(void)
{
    spdlog::trace("{} IN ()", __PRETTY_FUNCTION__);
    float yaw = _camera.yaw();
    float pitch = _camera.pitch();

    Command *cmd;

    // Obtain the deltas in cursor position.
    float dx = _cursorData.axis.x - _prevCursorData.axis.x;
    float dy = _prevCursorData.axis.y - _cursorData.axis.y;

    // Update the Previous Cursor Position Data.
    _prevCursorData = _cursorData;

    // Avoid spikes in the direction.
    if (dx > 100 || dy > 100)
    {
        return;
    }

    // If an update occured, move the camera direction.
    if (dx != 0 || dy != 0)
    {
        // Calculate the new direction.
        yaw += dx * static_cast<float>(LOOK_SPEED);
        pitch += dy * static_cast<float>(LOOK_SPEED);

        // Create the command.
        cmd = new LookCommand(&_camera, yaw, pitch);
        cmd->execute();
        delete cmd;
    }
    spdlog::trace("{} OUT ()", __PRETTY_FUNCTION__);
}
