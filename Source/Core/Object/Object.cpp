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
    DEBUG_PRINTF("Entry")
	printf("Created object: %s\n", argObjectName.c_str());
}

Object::~Object()
{
    DEBUG_PRINTF("Entry")
}

std::string Object::GetObjectName(void)
{
    DEBUG_PRINTF("Entry")
	return this->_objectName;
}

std::string Object::GetClassName(void)
{
    DEBUG_PRINTF("Entry")
	return this->_className;
}

glm::vec3 Object::GetPosition(void)
{
    DEBUG_PRINTF("Entry")
	return this->_position;
}

glm::vec3 Object::GetRotation(void)
{
    DEBUG_PRINTF("Entry")
	return this->_rotation;
}

glm::vec3 Object::GetScale(void)
{
    DEBUG_PRINTF("Entry")
	return this->_scale;
}

glm::vec3 Object::SetPosition(glm::vec3 argPosition)
{
    DEBUG_PRINTF("Entry")
	this->_position = argPosition;
	return this->_position;
}

glm::vec3 Object::SetRotation(glm::vec3 argRotation)
{
    DEBUG_PRINTF("Entry")
	this->_rotation = argRotation;
	return this->_rotation;
}

glm::vec3 Object::SetScale(glm::vec3 argScale)
{
    DEBUG_PRINTF("Entry")
	this->_scale = argScale;
	return this->_scale;
}

void Object::Rotate(glm::vec3 argRotation)
{
    DEBUG_PRINTF("Entry")
	this->SetRotation(argRotation);
}

void Object::UseShader(ShaderProgram &shader)
{
    DEBUG_PRINTF("Entry")
    // Ensure that the shader is ready to be used.
    if (shader.isReadyToUse() != true)
    {
        std::cerr << "Region::useShader Shader is not ready to use" << std::endl;
        return;
    }

    // Save the shader reference being used.
    this->_shaderProgram = shader;

    // Indicate that the program is being used for OpenGL.
    this->_shaderProgram.use();
}
