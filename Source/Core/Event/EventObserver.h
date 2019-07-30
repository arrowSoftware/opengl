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
/// This file contains a base class representation of the interface used to
/// observe events that are passed throughout the application. The input manager
/// is one source of generating events.
////////////////////////////////////////////////////////////////////////////////
#ifndef _EVENT_OBSERVER_H_
#define _EVENT_OBSERVER_H_

// Project Includes.
#include "Event.h"

class EventObserver
{
    public:
        ////////////////////////////////////////////////////////////////////////
        // Function:
        //    ~EventObserver.
        // Description:
        //    Deconstructs the object.
        // Parameters:
        //    None.
        // Returns:
        //    None.
        ////////////////////////////////////////////////////////////////////////
        virtual ~EventObserver(void);

        ////////////////////////////////////////////////////////////////////////
        // Function:
        //    onEvent.
        // Description:
        //    Callback handler for the event emitted.
        // Parameters:
        //    argEvent: The event emitted.
        // Returns:
        //    None.
        ////////////////////////////////////////////////////////////////////////
        virtual void onEvent(ApplicationEventStruct argEvent) = 0;
};

#endif // _EVENT_OBSERVER_H_
