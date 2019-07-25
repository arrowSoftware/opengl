
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
static const float MOVEMENT_SPEED = 0.5;

// This is the cameras look speed, or mouse speed.
static const float LOOK_SPEED = 0.25;

CameraController::CameraController(void)
{
    spdlog::trace("{} IN ()", __PRETTY_FUNCTION__);

    // set the event states to the initial max size.
    _eventStates.resize(ApplicationEventEnum::AE_MAX_EVENT_ENUM);

    spdlog::trace("{} OUT ()", __PRETTY_FUNCTION__);
}

void CameraController::registerWith(InputManager &manager)
{
    spdlog::trace("{} IN ()", __PRETTY_FUNCTION__);

    // Register to be notified for the following events.
    manager.RegisterInput(AE_MOVE_FORWARD, this);
    manager.RegisterInput(AE_MOVE_BACKWARD, this);
    manager.RegisterInput(AE_MOVE_LEFT, this);
    manager.RegisterInput(AE_MOVE_RIGHT, this);
    manager.RegisterInput(AE_MOVE_UP, this);
    manager.RegisterInput(AE_MOVE_DOWN, this);
    manager.RegisterInput(AE_LOOK_AROUND, this);
    spdlog::trace("{} OUT ()", __PRETTY_FUNCTION__);
}

void CameraController::OnEvent(ApplicationEventStruct event)
{
    spdlog::trace("{} IN ()", __PRETTY_FUNCTION__);
    if (event.type != AE_REPEAT)
    {
        mEventStates[event.code] = event.type;
    }

    switch(event.code)
    {
        case AE_LOOK_AROUND:
            mCursorData = event.data;
            break;

        default:
            break;
    }
    spdlog::trace("{} OUT ()", __PRETTY_FUNCTION__);
}

void CameraController::update(void)
{
    spdlog::trace("{} IN ()", __PRETTY_FUNCTION__);
    updatePosition();
    updateFacing();
    spdlog::trace("{} OUT ()", __PRETTY_FUNCTION__);
}

glm::mat4 CameraController::getView(void)
{
    spdlog::trace("{} IN ()", __PRETTY_FUNCTION__);
    spdlog::trace("{} OUT ()", __PRETTY_FUNCTION__);
    return _camera.GetView();
}

glm::vec3 CameraController::getPosition(void)
{
    spdlog::trace("{} IN ()", __PRETTY_FUNCTION__);
    spdlog::trace("{} OUT ()", __PRETTY_FUNCTION__);
    return _camera.GetPosition();
}

void CameraController::updatePosition(void)
{
    spdlog::trace("{} IN ()", __PRETTY_FUNCTION__);
    glm::vec3 position = _camera.GetPosition();
    glm::vec3 direction = _camera.GetFacing();
    glm::vec3 deltaPos = glm::vec3(0);

    Command *cmd;

    // Calculate the new position of the Camera based upon which events have
    // been received.
    if (mEventStates[AE_MOVE_BACKWARD] == AE_BEGIN)
    {
        deltaPos -= direction;
    }
    if (mEventStates[AE_MOVE_FORWARD] == AE_BEGIN)
    {
        deltaPos += direction;
    }
    if (mEventStates[AE_MOVE_LEFT] == AE_BEGIN)
    {
        deltaPos -= glm::normalize(glm::cross(
                direction,
                VECTOR_UP));
    }
    if (mEventStates[AE_MOVE_RIGHT] == AE_BEGIN)
    {
        deltaPos += glm::normalize(glm::cross(
                direction,
                VECTOR_UP));
    }
    if (mEventStates[AE_MOVE_UP] == AE_BEGIN)
    {
        deltaPos += VECTOR_UP;
    }
    if (mEventStates[AE_MOVE_DOWN] == AE_BEGIN)
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
    cmd = new MoveCommand(&_camera, position + deltaPos);
    cmd->Execute();
    delete cmd;

    spdlog::trace("{} OUT ()", __PRETTY_FUNCTION__);
}

void CameraController::updateFacing(void)
{
    spdlog::trace("{} IN ()", __PRETTY_FUNCTION__);
    float yaw = _camera.GetYaw();
    float pitch = _camera.GetPitch();

    Command *cmd;

    // Obtain the deltas in cursor position.
    float dx = mCursorData.axis.x - mPrevCursorData.axis.x;
    float dy = mPrevCursorData.axis.y - mCursorData.axis.y;

    // Update the Previous Cursor Position Data.
    mPrevCursorData = mCursorData;

    // Avoid spikes in the direction.
    if (dx > 100 || dy > 100)
    {
        return;
    }

    // If an update occured, move the camera direction.
    if (dx != 0 || dy != 0)
    {
        // Calculate the new direction.
        yaw += dx * LOOK_SPEED;
        pitch += dy * LOOK_SPEED;

        // Create the command.
        cmd = new LookCommand(&_camera, yaw, pitch);
        cmd->Execute();
        delete cmd;
    }
    spdlog::trace("{} OUT ()", __PRETTY_FUNCTION__);
}
