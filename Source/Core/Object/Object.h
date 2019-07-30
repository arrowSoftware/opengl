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
#ifndef _OBJECT_H_
#define _OBJECT_H_

// STL Includes.
#include <string>
#include <iostream>
#include <sstream>

// OpenGL Includes.
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#ifdef _OSX_
#include <GLUT/glut.h>
#else // _WINDOWS_, _LINUX_
#include <GL/glut.h>
#endif // OSX
#include <GLFW/glfw3.h>

// Project Includes.
#include "ShaderProgram.h"

// This create the pivate className and public accessor each each class
// derived from the object class. It is intended that this be placed in the
// "global" space of each derived class.
#define OBJECT(name) \
private: \
    std::string _className = #name; \
public: \
    std::string className(void) {return this->_className;}

class Object
{
    public:
        ////////////////////////////////////////////////////////////////////////
        // Function:
        //    Object
        // Description:
        //    Constructs the Object instance.
        // Parameters:
        //    argObjectName: The name of the object to construct.
        // Returns:
        //    Object.
        ////////////////////////////////////////////////////////////////////////
        Object(std::string argObjectName);

        ////////////////////////////////////////////////////////////////////////
        // Function:
        //    ~Object
        // Description:
        //    Deconstructs the object.
        // Parameters:
        //    None.
        // Returns:
        //    None.
        ////////////////////////////////////////////////////////////////////////
        virtual ~Object(void);

        ////////////////////////////////////////////////////////////////////////
        // Function:
        //    objectName.
        // Description:
        //    Get the object name.
        // Parameters:
        //    None.
        // Returns:
        //    std::string object name.
        ////////////////////////////////////////////////////////////////////////
        std::string objectName(void);

        ////////////////////////////////////////////////////////////////////////
        // Function:
        //    className.
        // Description:
        //    Get the name of the c++ class.
        // Parameters:
        //    None.
        // Returns:
        //    std::string class name.
        ////////////////////////////////////////////////////////////////////////
        virtual std::string className(void);

        ////////////////////////////////////////////////////////////////////////
        // Function:
        //    position
        // Description:
        //    Get the position of the object.
        // Parameters:
        //    None.
        // Returns:
        //    glm::vec3 position
        ////////////////////////////////////////////////////////////////////////
        glm::vec3 position(void);

        ////////////////////////////////////////////////////////////////////////
        // Function:
        //    rotation
        // Description:
        //    Get the rotation of the object.
        // Parameters:
        //    None.
        // Returns:
        //    glm::vec3 rotation
        ////////////////////////////////////////////////////////////////////////
        glm::vec3 rotation(void);

        ////////////////////////////////////////////////////////////////////////
        // Function:
        //    scale
        // Description:
        //    Get the scale of the object.
        // Parameters:
        //    None.
        // Returns:
        //    glm::vec3 scale
        ////////////////////////////////////////////////////////////////////////
        glm::vec3 scale(void);

        ////////////////////////////////////////////////////////////////////////
        // Function:
        //    SetPosition
        // Description:
        //    Set the position of the object.
        // Parameters:
        //    argPosition: Position to set.
        // Returns:
        //    glm::vec3 New position of the object.
        ////////////////////////////////////////////////////////////////////////
        glm::vec3 setPosition(glm::vec3 argPosition);

        ////////////////////////////////////////////////////////////////////////
        // Function:
        //    SetRotation
        // Description:
        //    Set the rotation of the object.
        // Parameters:
        //    argRotation: rotation to set.
        // Returns:
        //    glm::vec3 New rotation of the object.
        ////////////////////////////////////////////////////////////////////////
        glm::vec3 setRotation(glm::vec3 argRotation);

        ////////////////////////////////////////////////////////////////////////
        // Function:
        //    SetScale
        // Description:
        //    Set the scale of the object.
        // Parameters:
        //    argScale: Position to set.
        // Returns:
        //    glm::vec3 New scale of the object.
        ////////////////////////////////////////////////////////////////////////
        glm::vec3 setScale(glm::vec3 argScale);

        ////////////////////////////////////////////////////////////////////////
        // Function:
        //    draw.
        // Description:
        //    Draw the object. Must be draw each OpenGL redraw cycle.
        // Parameters:
        //    None.
        // Returns:
        //    None.
        ////////////////////////////////////////////////////////////////////////
        virtual void draw(void) = 0;

        ////////////////////////////////////////////////////////////////////////
        // Function:
        //    initialize.
        // Description:
        //    Initialize the object.
        // Parameters:
        //    None.
        // Returns:
        //    None.
        ////////////////////////////////////////////////////////////////////////
        virtual void initialize(void) = 0;

        ////////////////////////////////////////////////////////////////////////
        // Function:
        //    wrapup
        // Description:
        //    Cleanup the object.
        // Parameters:
        //    None.
        // Returns:
        //    None.
        ////////////////////////////////////////////////////////////////////////
        virtual void wrapup(void) = 0;

        ////////////////////////////////////////////////////////////////////////
        // Function:
        //    useShader
        // Description:
        //    This will cause OpenGL to process the shader program.
        // Parameters:
        //    argShader: Which shader to use.
        // Returns:
        //    None.
        ////////////////////////////////////////////////////////////////////////
        void useShader(ShaderProgram &argShader);

    protected:
        // Name of this object.
        std::string _objectName;

        // Name of this class.
        std::string _className;

        // Position of this object.
        glm::vec3 _position;

        // Rotation of this object.
        glm::vec3 _rotation;

        // Scale of this object.
        glm::vec3 _scale;

        // Shader program of this object.
        ShaderProgram _shaderProgram;

        // Shader program view point.
        GLuint _uniformVP;

        // Shader program model.
        GLuint _uniformModel;
};

#endif // _OBJECT_H_
