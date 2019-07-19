#pragma once

#include <string>
#include <iostream>
#include <sstream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <GLUT/glut.h>
#include <GLFW/glfw3.h>

#include "ShaderProgram.h"

#define OBJECT(name) \
private: \
	std::string _className = #name; \
public: \
	std::string ClassName(void) {return this->_className;}

class Object
{
	public:
		Object(std::string argObjectName);
		virtual ~Object(void);

		std::string ObjectName(void);
		virtual std::string ClassName(void);

		glm::vec3 Position(void);
		glm::vec3 Rotation(void);
		glm::vec3 Scale(void);

		glm::vec3 SetPosition(glm::vec3 argPosition);
		glm::vec3 SetRotation(glm::vec3 argRotation);
		glm::vec3 SetScale(glm::vec3 argScale);

		void Rotate(glm::vec3 argRotation);

		virtual void Draw(void) = 0;
        virtual void Initialize(void) = 0;
        virtual void Wrapup(void) = 0;
        void UseShader(ShaderProgram &shader);

	protected:
		std::string _objectName;
		std::string _className;

		glm::vec3 _position;
		glm::vec3 _rotation;
		glm::vec3 _scale;

        ShaderProgram _shaderProgram;
        GLuint mUniformVP;
        GLuint mUniformModel;
};
