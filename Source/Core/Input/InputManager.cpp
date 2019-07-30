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

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "InputManager.h"
#include "Utils.h"

InputManager::InputManager(void)
{
    DEBUG_PRINTF("Entry")
    // Resize the subscribers list to the maximum ApplicationEvent.
    mSubscribers.resize(AE_MAX_EVENT_ENUM);

    // Resize the keymap to the maximum GLFW Key Input.
    mKeyEventMap.resize(GLFW_KEY_LAST);

    // Set some default keys (TODO: Remove).
    mKeyEventMap[GLFW_KEY_W] = AE_MOVE_FORWARD;
    mKeyEventMap[GLFW_KEY_S] = AE_MOVE_BACKWARD;
    mKeyEventMap[GLFW_KEY_A] = AE_MOVE_LEFT;
    mKeyEventMap[GLFW_KEY_D] = AE_MOVE_RIGHT;
    mKeyEventMap[GLFW_KEY_SPACE] = AE_MOVE_UP;
    mKeyEventMap[GLFW_KEY_LEFT_SHIFT] = AE_MOVE_DOWN;
}

void InputManager::RegisterInput(
    ApplicationEventEnum code, EventObserver *observer)
{
    DEBUG_PRINTF("Entry")
    mSubscribers[code].push_back(observer);
}

void InputManager::KeyCallback(GLFWwindow *window, int key, int scancode,
    int action, int modifiers)
{
    DEBUG_PRINTF("Entry")
    ApplicationEventStruct event;

    // The code is stored in the keymap.
    event.code = mKeyEventMap[key];

    // The type depends upon the action.
    switch (action)
    {
        case GLFW_PRESS:
            event.type = AE_BEGIN;
            break;
        case GLFW_REPEAT:
            event.type = AE_REPEAT;
            break;
        case GLFW_RELEASE:
            event.type = AE_END;
            break;
    }

    EmitEvent(event);
}

void InputManager::MouseCallback(GLFWwindow *window, double xpos, double ypos)
{
    DEBUG_PRINTF("Entry")
    ApplicationEventStruct event;

    event.code = AE_LOOK_AROUND;
    event.type = AE_SINGLE;

    event.data.axis.x = xpos;
    event.data.axis.y = ypos;

    EmitEvent(event);
}

void InputManager::EmitEvent(ApplicationEventStruct event)
{
    DEBUG_PRINTF("Entry")
    for (EventObserver *observer : mSubscribers[event.code])
    {
        observer->OnEvent(event);
    }
}
