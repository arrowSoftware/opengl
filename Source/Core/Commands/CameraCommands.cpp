////////////////////////////////////////////////////////////////////////////////
/// This file contains several command classes that the Camera responds to. Most
/// of these commands are generated and responded to by the InputManager.
////////////////////////////////////////////////////////////////////////////////
#include "CameraCommands.h"
#include "Utils.h"

LookCommand::LookCommand(Camera *camera, float yaw, float pitch)
{
    DEBUG_PRINTF("Entry")
    mCamera = camera;
    mYaw = yaw;
    mPitch = pitch;
}

void LookCommand::Execute(void)
{
    DEBUG_PRINTF("Entry")
    mCamera->SetYaw(mYaw);
    mCamera->SetPitch(mPitch);
}

MoveCommand::MoveCommand(Camera *camera, glm::vec3 position)
{
    DEBUG_PRINTF("Entry")
    mCamera = camera;
    mPosition = position;
}

void MoveCommand::Execute(void)
{
    DEBUG_PRINTF("Entry")
    mCamera->SetPosition(mPosition);
}