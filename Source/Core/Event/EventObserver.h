////////////////////////////////////////////////////////////////////////////////
/// This file contains a base class representation of the interface used to
/// observe events that are passed throughout the application. The input manager
/// is one source of generating events.
////////////////////////////////////////////////////////////////////////////////
#ifndef _EVENT_OBSERVER_H_
#define _EVENT_OBSERVER_H_

// Project Includes.
#include "Event.h"

/// This is the base class for listening to events. All subclasses must
/// implement the onEvent method to receive an event.
class EventObserver
{
    public:
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
        virtual ~EventObserver(void);

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
        virtual void OnEvent(ApplicationEventStruct event) = 0;
};

#endif // _EVENT_OBSERVER_H_
