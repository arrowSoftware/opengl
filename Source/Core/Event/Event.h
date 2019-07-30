////////////////////////////////////////////////////////////////////////////////
// File:
//    Event.h
// Description:
//    This file contains data that relates to events emitted by the input manager.
// Methods:
//    None.
// Fields:
//    ApplicationEventEnum aka app_event_enum_t
//    ApplicationEventType aka app_event_type_t
//      ApplicationEventAxisStruct aka app_event_axis_t
//      ApplicationEventDataStruct aka app_event_data_t
//    ApplicationEventStruct aka app_event_struct_t
// Modification History:
//    Date:        Who:            What:
//  07/25/2019  Tyler Gajewski    Initial Creation
////////////////////////////////////////////////////////////////////////////////

#ifndef _EVENT_H_
#define _EVENT_H_

// STL Includes.
#include <cstdio>

// This is a list of all events that can happen.
typedef enum ApplicationEventEnum
{
    AE_NO_EVENT = 0,
    AE_MOVE_FORWARD,
    AE_MOVE_BACKWARD,
    AE_MOVE_LEFT,
    AE_MOVE_RIGHT,
    AE_MOVE_UP,
    AE_MOVE_DOWN,
    AE_LOOK_AROUND,
    AE_MAX_EVENT_ENUM
} app_event_enum_t;

// This is a list of the type of events.
typedef enum ApplicationEventType
{
    AE_NONE = 0,
    AE_BEGIN,
    AE_END,
    AE_REPEAT,
    AE_SINGLE,
    AE_MAX_EVENT_TYPE_ENUM
} app_event_type_t;

// This is the data for a xyz coords.
typedef struct ApplicationEventAxisStruct
{
    float x;
    float y;
    float z;
} app_event_axis_t;

// This is the data associated with an event.
typedef struct ApplicationEventDataStruct
{
    app_event_axis_t axis;
} app_event_data_t;

// This is the application event.
typedef struct ApplicationEventStruct
{
    app_event_enum_t code;
    app_event_type_t type;
    app_event_data_t data;

    void print(void)
    {
        printf("code: %d\n", this->code);
        printf("type: %d\n", this->type);
        printf("data.axis:\n");
        printf("\tx: %f\n", this->data.axis.x);
        printf("\ty: %f\n", this->data.axis.y);
        printf("\tz: %f\n", this->data.axis.z);
    }
} app_event_struct_t;

#endif // _EVENT_H_
