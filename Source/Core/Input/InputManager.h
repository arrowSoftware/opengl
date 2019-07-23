////////////////////////////////////////////////////////////////////////////////
/// @file InputManager.hpp
/// @brief A class that converts input events into game inputs.
///
/// This class manages the low level input events and maps them to game events.
/// It also manages the mapping of keys to game controls. It functions by
/// emitting an event when a key is pressed and when a key is released. These
/// are the eventStart and eventEnd events. Other logic may be used to release
/// a series of events.
////////////////////////////////////////////////////////////////////////////////

#ifndef _INPUT_MANAGER_H_
#define _INPUT_MANAGER_H_

#include <list>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "EventObserver.h"

/// This class handles the GLFW input methods and converts the data into an
/// application event. It also is the subject of the observer pattern; it will
/// notify all registered observers when an event occurs.
class InputManager
{
    public:
        /// Constructs an input manager instance.
        ////////////////////////////////////////////////////////////////////////
        // Function:
        //
        // Description:
        //
        // Parameters:
        //
        // Returns:
        //
        ////////////////////////////////////////////////////////////////////////
        InputManager(void);

        /// This function is used to register event callbacks with the InputManager.
        ////////////////////////////////////////////////////////////////////////
        // Function:
        //
        // Description:
        //
        // Parameters:
        //
        // Returns:
        //
        ////////////////////////////////////////////////////////////////////////
        void RegisterInput(ApplicationEventEnum code, EventObserver *observer);

        /// This function processes GLFW Key Events and converts them to application
        /// events.
        ////////////////////////////////////////////////////////////////////////
        // Function:
        //
        // Description:
        //
        // Parameters:
        //
        // Returns:
        //
        ////////////////////////////////////////////////////////////////////////
        void KeyCallback(GLFWwindow *window, int key, int scancode,
            int action, int modifiers);

        /// This function processes GLFW Mouse Events and converts them to
        /// application events.
        ////////////////////////////////////////////////////////////////////////
        // Function:
        //
        // Description:
        //
        // Parameters:
        //
        // Returns:
        //
        ////////////////////////////////////////////////////////////////////////
        void MouseCallback(GLFWwindow *window, double xpos, double ypos);

        /// This function sends an event to all registered EventObservers.
        ////////////////////////////////////////////////////////////////////////
        // Function:
        //
        // Description:
        //
        // Parameters:
        //
        // Returns:
        //
        ////////////////////////////////////////////////////////////////////////
        void EmitEvent(ApplicationEventStruct event);

    private:

        /// Each index in the vector corresponds to a single ApplicationEventEnum.
        /// The vector stores a list of observers that will be notified when the
        /// corresponding event occurs.
        std::vector<std::list<EventObserver *>> mSubscribers;

        /// This structure maps GLFW keys to Application Event Types. The index into
        /// the vector is the key, and the value at that index is an event that is
        /// mapped to that key. Note that this only allows for one event per key
        /// input.
        std::vector<ApplicationEventEnum> mKeyEventMap;
};

#endif
