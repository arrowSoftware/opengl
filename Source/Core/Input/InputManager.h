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
////////////////////////////////////////////////////////////////////////////////
/// @file InputManager.hpp
/// @brief A class that converts input events into game inputs.
///
/// This class manages the low level input events and maps them to game events.
/// It also manages the mapping of keys to game controls. It functions by
/// emitting an event when a key is pressed and when a key is released. These
/// are the eventStart and eventEnd events. Other logic may be used to release
/// a series of events. It handles the GLFW input methods and converts the data
/// into an application event. It also is the subject of the observer pattern.
/// it will notify all registered observers when an event occurs.
////////////////////////////////////////////////////////////////////////////////

#ifndef SOURCE_CORE_INPUT_INPUTMANAGER_H_
#define SOURCE_CORE_INPUT_INPUTMANAGER_H_

// OpenGL Includes.
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// STL Includes.
#include <list>
#include <vector>

// Project Includes.
#include "EventObserver.h"

class InputManager
{
    public:
        ////////////////////////////////////////////////////////////////////////
        // Function:
        //    InputManager.
        // Description:
        //    Constructs an input manager instance.
        // Parameters:
        //    None.
        // Returns:
        //    InputManager
        ////////////////////////////////////////////////////////////////////////
        InputManager(void);

        ////////////////////////////////////////////////////////////////////////
        // Function:
        //    registerInput.
        // Description:
        //    This function is used to register event callbacks with the
        //  InputManager.
        // Parameters:
        //    argCode: Which event to register.
        //    argObserver: Who is registering.
        // Returns:
        //    None.
        ////////////////////////////////////////////////////////////////////////
        void registerInput(ApplicationEventEnum argCode,
                           EventObserver *argObserver);

        ////////////////////////////////////////////////////////////////////////
        // Function:
        //    keyCallback.
        // Description:
        //  This function processes GLFW Key Events and converts them to
        //  application events.
        // Parameters:
        //    argWindow: glfw window to process keybord input.
        //    argKey:    Which key was pressed.
        //    argScancode: Scancode of the pressed key.
        //    argAction: How it was pressed, press, release.
        //    argModifiers: Shift/Control/Alt.
        // Returns:
        //    None
        ////////////////////////////////////////////////////////////////////////
        void keyCallback(GLFWwindow *argWindow,
                         int argKey,
                         int argScancode,
                         int argAction,
                         int argModifiers);

        ////////////////////////////////////////////////////////////////////////
        // Function:
        //    mouseCallback
        // Description:
        //    This function processes GLFW Mouse Events and converts them to
        //    application events.
        // Parameters:
        //    argWindow: glfw window to proces mouse input.
        //    argXpos: X position of the mouse.
        //    argYpos: Y position of the mouse.
        // Returns:
        //    None.
        ////////////////////////////////////////////////////////////////////////
        void mouseCallback(GLFWwindow *argWindow,
                           double argXpos,
                           double argYpos);

        ////////////////////////////////////////////////////////////////////////
        // Function:
        //    emitEvent
        // Description:
        //    This function sends an event to all registered EventObservers.
        // Parameters:
        //    argEvent: The evant to emit.
        // Returns:
        //    None.
        ////////////////////////////////////////////////////////////////////////
        void emitEvent(ApplicationEventStruct argEvent);

    private:
        // Each index in the vector corresponds to a single
        // ApplicationEventEnum. The vector stores a list of observers that will
        // be notified when the corresponding event occurs. It is sixed in the
        // contrustor to the largest value in the ApplicationEventEnum.
        std::vector<std::list<EventObserver *>> _subscribers;

        // This structure maps GLFW keys to Application Event Types. The index
        // into the vector is the key, and the value at that index is an event
        // that is mapped to that key. Note that this only allows for one event
        // per key input.
        std::vector<ApplicationEventEnum> _keyEventMap;
};

#endif // SOURCE_CORE_INPUT_INPUTMANAGER_H_
