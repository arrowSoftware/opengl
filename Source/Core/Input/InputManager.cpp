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
    // Resize the subscribers list to the maximum ApplicationEvent.
    _subscribers.resize(AE_MAX_EVENT_ENUM);

    // Resize the keymap to the maximum GLFW Key Input.
    _keyEventMap.resize(GLFW_KEY_LAST);

    // Set some default keys (TODO: Remove).
    _keyEventMap[GLFW_KEY_W] = AE_MOVE_FORWARD;
    _keyEventMap[GLFW_KEY_S] = AE_MOVE_BACKWARD;
    _keyEventMap[GLFW_KEY_A] = AE_MOVE_LEFT;
    _keyEventMap[GLFW_KEY_D] = AE_MOVE_RIGHT;
    _keyEventMap[GLFW_KEY_SPACE] = AE_MOVE_UP;
    _keyEventMap[GLFW_KEY_LEFT_SHIFT] = AE_MOVE_DOWN;
}

void InputManager::registerInput(
    ApplicationEventEnum code, EventObserver *observer)
{
    _subscribers[code].push_back(observer);
}

void InputManager::keyCallback(GLFWwindow *window, int key, int scancode,
    int action, int modifiers)
{
    ApplicationEventStruct event;

    // The code is stored in the keymap.
    event.code = _keyEventMap[(unsigned long)key];

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

    emitEvent(event);
}

void InputManager::mouseCallback(GLFWwindow *window, double xpos, double ypos)
{
    ApplicationEventStruct event;

    event.code = AE_LOOK_AROUND;
    event.type = AE_SINGLE;

    event.data.axis.x = (float)xpos;
    event.data.axis.y = (float)ypos;

    emitEvent(event);
}

void InputManager::emitEvent(ApplicationEventStruct event)
{
    for (EventObserver *observer : _subscribers[event.code])
    {
        observer->onEvent(event);
    }
}
