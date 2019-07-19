#ifndef _CAMERA_CONTROLLER_H_
#define _CAMERA_CONTROLLER_H_

#include <vector>

#include "Camera.h"
#include "EventObserver.h"
#include "InputManager.h"

class CameraController : public EventObserver
{
public:
    CameraController(void);
    void registerWith(InputManager &manager);
    virtual void OnEvent(ApplicationEventStruct event);
    void update(void);
    glm::mat4 getView(void);
    glm::vec3 getPosition(void);

private:
    Camera mCamera;
    std::vector<ApplicationEventType> mEventStates;
    ApplicationEventDataStruct mCursorData;
    ApplicationEventDataStruct mPrevCursorData;

    void updatePosition(void);
    void updateFacing(void);
};

#endif
