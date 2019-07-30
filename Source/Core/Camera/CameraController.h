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
#ifndef _CAMERA_CONTROLLER_H_
#define _CAMERA_CONTROLLER_H_

// STL Includes.
#include <vector>

// Project Includes.
#include "Camera.h"
#include "EventObserver.h"
#include "InputManager.h"

class CameraController : public EventObserver
{
    public:
        ////////////////////////////////////////////////////////////////////////
        // Function:
        //  CameraController
        // Description:
        //  Create a controller to manage a camera.
        // Parameters:
        //  None.
        // Returns:
        //  CameraController object.
        ////////////////////////////////////////////////////////////////////////
        CameraController(void);

        ////////////////////////////////////////////////////////////////////////
        // Function:
        //  registerWith
        // Description:
        //  This function registers this camera controller with an input manager
        //  for receiving input events.
        // Parameters:
        //  argManager: The input manager to register with.
        // Returns:
        //  None.
        ////////////////////////////////////////////////////////////////////////
        void registerWith(InputManager &argManager);

        ////////////////////////////////////////////////////////////////////////
        // Function:
        //  onEvent
        // Description:
        //  This is the main callback function for when a registers event.
        //  It will process the passed in event if it knows how.
        //  occurs.
        // Parameters:
        //  argEvent: The event that is occuring.
        // Returns:
        //  None.
        ////////////////////////////////////////////////////////////////////////
        virtual void onEvent(ApplicationEventStruct argEvent);

        ////////////////////////////////////////////////////////////////////////
        // Function:
        //  update
        // Description:
        //  This will update information about the camera, look, move, position.
        // Parameters:
        //  None.
        // Returns:
        //  None.
        ////////////////////////////////////////////////////////////////////////
        void update(void);

        ////////////////////////////////////////////////////////////////////////
        // Function:
        //  view
        // Description:
        //  This will return the view of the camera.
        // Parameters:
        //  None.
        // Returns:
        //  glm::mat4 view of the camera.
        ////////////////////////////////////////////////////////////////////////
        glm::mat4 view(void);

        ////////////////////////////////////////////////////////////////////////
        // Function:
        //  position
        // Description:
        //  This will return the position of the camera.
        // Parameters:
        //  None.
        // Returns:
        //  glm::vec3 position of the camera.
        ////////////////////////////////////////////////////////////////////////
        glm::vec3 position(void);

    private:
        // The attached camera.
        Camera _camera;

        // This is a vector of all the states this controller can process.
        std::vector<ApplicationEventType> _eventStates;

        // This is the current mouse cursor information.
        ApplicationEventDataStruct _cursorData;

        // This is the previous mouse cursor information.
        ApplicationEventDataStruct _prevCursorData;

        ////////////////////////////////////////////////////////////////////////
        // Function:
        //  updatePosition
        // Description:
        //  This will update the position of the camera with commands.
        // Parameters:
        //  None.
        // Returns:
        //  None.
        ////////////////////////////////////////////////////////////////////////
        void updatePosition(void);

        ////////////////////////////////////////////////////////////////////////
        // Function:
        //  updateFacing
        // Description:
        //  This will update the facing of the camera.
        // Parameters:
        //  None.
        // Returns:
        //  None.
        ////////////////////////////////////////////////////////////////////////
        void updateFacing(void);
};

#endif // _CAMERA_CONTROLLER_H_
