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

#include "Object.h"
#include "Utils.h"
#include <stdio.h>

Object::Object(std::string argObjectName) :
    _objectName(argObjectName),
        _className("Object"),
    _position(glm::vec3(0, 0, 0)),
    _rotation(glm::vec3(0, 0, 0)),
    _scale(glm::vec3(1, 1, 1))
{
    printf("Created object: %s\n", argObjectName.c_str());
}

Object::~Object()
{
}

std::string Object::objectName(void)
{
    return this->_objectName;
}

std::string Object::className(void)
{
    return this->_className;
}

glm::vec3 Object::position(void)
{
    return this->_position;
}

glm::vec3 Object::rotation(void)
{
    return this->_rotation;
}

glm::vec3 Object::scale(void)
{
    return this->_scale;
}

glm::vec3 Object::setPosition(glm::vec3 argPosition)
{
    this->_position = argPosition;
    return this->_position;
}

glm::vec3 Object::setRotation(glm::vec3 argRotation)
{
    this->_rotation = argRotation;
    return this->_rotation;
}

glm::vec3 Object::setScale(glm::vec3 argScale)
{
    this->_scale = argScale;
    return this->_scale;
}

void Object::useShader(ShaderProgram &shader)
{
    // Ensure that the shader is ready to be used.
    if (shader.isReadyToUse() != true)
    {
        std::cerr << "Region::useShader Shader is not ready to use"
                  << std::endl;
        return;
    }

    // Save the shader reference being used.
    this->_shaderProgram = shader;

    // Indicate that the program is being used for OpenGL.
    this->_shaderProgram.use();
}
