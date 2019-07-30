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
/// @file ShaderProgram.cpp
/// @brief A class to handle GLSL shaders.
///
/// This file contains the GLSL shader class. It is responsible for loading,
/// compiling, and attaching shaders. Each instance of this class contains one
/// vertex shader and one fragment shader.
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <sstream>
#include <fstream>

#include "ShaderProgram.h"
#include "ApplicationException.hpp"
#include "Utils.h"

ShaderProgram::ShaderProgram(std::string vertex, std::string fragment)
{
    bool status = false;

    // Construct the Vertex Shader.
    status = useVertexShader(vertex);
    if (status == false)
    {
        throw ApplicationException("Unable to create vertex shader");
    }

    // Construct the Fragment Shader.
    status = useFragmentShader(fragment);
    if (status == false)
    {
        throw ApplicationException("Unable to create fragment shader");
    }

    // Construct the Program.
    status = linkProgram();
    if (status == false)
    {
        throw ApplicationException("Unable to create shader program");
    }
}

ShaderProgram::ShaderProgram(void)
{
    // Set the Compiled and Linked flag to false indicating that a complete
    // program was not made.
    _compiledAndLinked = false;

    // Set the OpenGL variables.
    _vertexShader = 0;
    _fragmentShader = 0;
    _program = 0;
}

ShaderProgram::~ShaderProgram(void)
{
    glDeleteProgram(_program);
    glDeleteShader(_vertexShader);
    glDeleteShader(_fragmentShader);
}

bool ShaderProgram::isReadyToUse(void)
{
    // The program is ready to use if it has shaders that have been compiled and
    // linked.
    return _compiledAndLinked;
}

bool ShaderProgram::useVertexShader(std::string vertex)
{
    GLint glResult = GL_FALSE;

    // By setting a new vertex shader, the program must be relinked in order to
    // use it.
    _compiledAndLinked = false;

    // If a previous vertex shader exists, then mark it for deletion. OpenGL
    // will not delete the shader until it is no longer in context (i.e. if it
    // is part of the active shader program, it won't get deleted until a new
    // program is used).
    if (_vertexShader != 0)
    {
        glDeleteShader(_vertexShader);
    }

    // Save the filename and source of the file.
    _vertexFile = vertex;
    _vertexSource = readFile(_vertexFile);

    // Construct the new vertex shader.
    _vertexShader = glCreateShader(GL_VERTEX_SHADER);
    if (_vertexShader == 0)
    {
        return false;
    }

    const GLchar *sourceCString = _vertexSource.c_str();
    glShaderSource(_vertexShader, 1, &sourceCString, NULL);
    glCompileShader(_vertexShader);
    glGetShaderiv(_vertexShader, GL_COMPILE_STATUS, &glResult);
    if (GL_FALSE == glResult)
    {
        printInfoLog(_vertexShader);
        glDeleteShader(_vertexShader);
        _vertexShader = 0;
        return false;
    }

    return true;
}

bool ShaderProgram::useFragmentShader(std::string fragment)
{
    GLint glResult = GL_FALSE;

    // By setting a new fragment shader, the program must be relinked in order
    // to use it.
    _compiledAndLinked = false;

    // If a previous fragment shader exists, then mark it for deletion. OpenGL
    // will not delete the shader until it is no longer in context (i.e. if it
    // is part of the active shader program, it won't get deleted until a new
    // program is used).
    if (_fragmentShader != 0)
    {
        glDeleteShader(_fragmentShader);
    }

    // Save the filename and source of the file.
    _fragmentFile = fragment;
    _fragmentSource = readFile(_fragmentFile);

    // Construct the new fragment shader.
    _fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    if (_fragmentShader == 0)
    {
        return false;
    }

    const GLchar *sourceCString = _fragmentSource.c_str();
    glShaderSource(_fragmentShader, 1, &sourceCString, NULL);
    glCompileShader(_fragmentShader);
    glGetShaderiv(_fragmentShader, GL_COMPILE_STATUS, &glResult);
    if (GL_FALSE == glResult)
    {
        printInfoLog(_fragmentShader);
        glDeleteShader(_fragmentShader);
        _fragmentShader = 0;
        return false;
    }

    return true;
}

bool ShaderProgram::linkProgram(void)
{
    GLint glResult = GL_FALSE;

    // If the program is already compiled and linked (signaling that no new
    // shader has been added), then simply return true.
    if (_compiledAndLinked == true)
    {
        return true;
    }

    // If either the vertex or the fragment shader is missing, then do not link
    // the program.
    if (_vertexShader == 0 || _fragmentShader == 0)
    {
        return false;
    }

    // Otherwise, we need to relink the program. If a previous program exists,
    // then we mark it for deletion. OpenGL won't delete the program if it is
    // active untile another program is being used.
    if (_program != 0)
    {
        glDeleteProgram(_program);
    }

    // Construct the new program.
    _program = glCreateProgram();
    if (_program == 0)
    {
        return false;
    }

    glAttachShader(_program, _vertexShader);
    glAttachShader(_program, _fragmentShader);
    glLinkProgram(_program);
    glGetProgramiv(_program, GL_LINK_STATUS, &glResult);
    if (GL_FALSE == glResult)
    {
        printInfoLog(_program);
        glDeleteProgram(_program);
        _program = 0;
        return false;
    }

    // Since the program linked successfully, it is ready to be used.
    _compiledAndLinked = true;
    return true;
}

void ShaderProgram::use(void)
{
    // Do not activate unless the program is ready.
    if (isReadyToUse() != true)
    {
        std::cerr << "ShaderProgram is not ready to use. Activate failed" <<
            std::endl;
        return;
    }

    glUseProgram(_program);
}

GLuint ShaderProgram::program(void)
{
    return _program;
}

GLuint ShaderProgram::uniformLocation(std::string uniform)
{
    GLuint loc = glGetUniformLocation(_program, uniform.c_str());
    if (loc == GL_INVALID_INDEX)
    {
        std::cerr << "ShaderProgram: unable to find uniform " << uniform <<
            std::endl;
    }
    return loc;
}

ShaderProgram& ShaderProgram::operator=(const ShaderProgram& other)
{
    if (_vertexShader != 0)
    {
        glDeleteShader(_vertexShader);
    }

    if (_fragmentShader != 0)
    {
        glDeleteShader(_fragmentShader);
    }

    if (_program != 0)
    {
        glDeleteProgram(_program);
    }

    _compiledAndLinked = other._compiledAndLinked;
    _vertexFile = other._vertexFile;
    _vertexSource = other._vertexSource;
    _vertexShader = other._vertexShader;
    _fragmentFile = other._fragmentFile;
    _fragmentSource = other._fragmentSource;
    _fragmentShader = other._fragmentShader;
    _program = other._program;

    return *this;
}

std::string ShaderProgram::readFile(std::string filename)
{
    std::ifstream input(filename);
    std::stringstream contents;

    if (input.good())
    {
        contents << input.rdbuf();

        if (contents.good())
        {
            return contents.str();
        }
        else
        {
            std::cerr << "ShaderProgram: Error reading file " << filename <<
                std::endl;
        }
    }
    else
    {
        std::cerr << "ShaderProgram: Unable to locate file " << filename <<
            std::endl;
    }

    return "";
}

void ShaderProgram::printInfoLog(GLuint object)
{
    GLuint logLength = 0;

    if (glIsShader(object))
    {
        glGetShaderiv(object, GL_INFO_LOG_LENGTH, &logLength);
    }
    else if (glIsProgram(object))
    {
        glGetProgramiv(object, GL_INFO_LOG_LENGTH, &logLength);
    }
    else
    {
        std::cerr << "ShaderProgram::printInfoLog object is not a shader " <<
            "or program)" << std::endl;
        return;
    }

    char * log = new char[logLength];

    if (glIsShader(object))
    {
        glGetShaderInfoLog(object, logLength, NULL, log);
    }
    else if (glIsProgram(object))
    {
        glGetProgramInfoLog(object, logLength, NULL, log);
    }

    std::cerr << "ShaderProgram Info Log:" << std::endl;
    std::cerr << log << std::endl;

    delete[] log;
}
