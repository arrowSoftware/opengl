////////////////////////////////////////////////////////////////////////////////
/// This file contains a base class representation of the interface used to
/// observe events that are passed throughout the application. The input manager
/// is one source of generating events.
////////////////////////////////////////////////////////////////////////////////
#ifndef _EVENT_OBSERVER_H_
#define _EVENT_OBSERVER_H_

#include "Event.h"

/// @class EventObserver
/// @brief A class to observe events.
///
/// This is the base class for listening to events. All subclasses must
/// implement the onEvent method to receive an event.
class EventObserver
{
    public:
        virtual ~EventObserver(void);
        virtual void OnEvent(ApplicationEventStruct event) = 0;
};

#endif // _EVENT_OBSERVER_H_
