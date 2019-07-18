#include "Object.h"

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

std::string Object::ObjectName(void)
{
	return this->_objectName;
}

std::string Object::ClassName(void)
{
	return this->_className;
}

glm::vec3 Object::Position(void)
{
	return this->_position;
}

glm::vec3 Object::Rotation(void)
{
	return this->_rotation;
}

glm::vec3 Object::Scale(void)
{
	return this->_scale;
}

glm::vec3 Object::SetPosition(glm::vec3 argPosition)
{
	this->_position = argPosition;
	return this->_position;
}

glm::vec3 Object::SetRotation(glm::vec3 argRotation)
{
	this->_rotation = argRotation;
	return this->_rotation;
}

glm::vec3 Object::SetScale(glm::vec3 argScale)
{
	this->_scale = argScale;
	return this->_scale;
}

void Object::Rotate(glm::vec3 argRotation)
{
	this->SetRotation(argRotation);
}
