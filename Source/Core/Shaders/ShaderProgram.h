////////////////////////////////////////////////////////////////////////////////
/// This file contains the GLSL shader class. It is responsible for loading,
/// compiling, and attaching shaders. Each instance of this class contains one
/// vertex shader and one fragment shader.
////////////////////////////////////////////////////////////////////////////////
#ifndef _SHADER_PROGRAM_H_
#define _SHADER_PROGRAM_H_

#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

/// The Shader Program Class contains methods for reading, compiling, and
/// linking a GLSL Shader Program.
class ShaderProgram
{
public:
    /// At construction time, the files representing the vertex and fragment
    /// shaders are read in and compiled and a Program is made and linked. If
    /// any error occurs here, an ApplicationException is thrown.
    ////////////////////////////////////////////////////////////////////////
    // Function:
    //
    // Description:
    //
    // Parameters:
    //
    // Returns:
    //
    ////////////////////////////////////////////////////////////////////////
    ShaderProgram(std::string vertex, std::string fragment);

    /// This creates an empty Shader Program. It is unable to be used until a
    /// vertex and fragment shader are added to it and a program is made via
    /// the linkProgram method.
    ////////////////////////////////////////////////////////////////////////
    // Function:
    //
    // Description:
    //
    // Parameters:
    //
    // Returns:
    //
    ////////////////////////////////////////////////////////////////////////
    ShaderProgram(void);

    /// This will free the OpenGL resources.
    ////////////////////////////////////////////////////////////////////////
    // Function:
    //
    // Description:
    //
    // Parameters:
    //
    // Returns:
    //
    ////////////////////////////////////////////////////////////////////////
    ~ShaderProgram(void);

    /// A Program is ready to be used if it has been compiled and linked, which
    /// is the status of the mCompiledAndLinked member variable.
    ///
    /// @returns True if the program has been compiled and linked or false if it
    /// has not been either compiled or linked.
    ////////////////////////////////////////////////////////////////////////
    // Function:
    //
    // Description:
    //
    // Parameters:
    //
    // Returns:
    //
    ////////////////////////////////////////////////////////////////////////
    bool isReadyToUse(void);

    /// This function will read the source of the file 'vertex' and compile it.
    /// Only one vertex shader can be associated with the shader program. If a
    /// previous vertex shader has been created, then it will be overwritten by
    /// the new one.
    ///
    /// @attention Creating a new shader requires the program to be relinked.
    /// @returns True if creation and compilation was successful or false if an
    /// error occured.
    ////////////////////////////////////////////////////////////////////////
    // Function:
    //
    // Description:
    //
    // Parameters:
    //
    // Returns:
    //
    ////////////////////////////////////////////////////////////////////////
    bool useVertexShader(std::string vertex);

    /// This function will read the source of the file 'fragment' and compile
    /// it. Only one fragment shader can be associated with the shader program.
    /// If a previous fragment shader has been created, then it will be
    /// overwritten by the new one.
    ///
    /// @attention Creating a new shader requires the program to be relinked.
    /// @returns True if creation and compilation was successful or false if an
    /// error occured.
    ////////////////////////////////////////////////////////////////////////
    // Function:
    //
    // Description:
    //
    // Parameters:
    //
    // Returns:
    //
    ////////////////////////////////////////////////////////////////////////
    bool useFragmentShader(std::string fragment);

    /// This function will attach the fragment and vertex shader and link it
    /// into a compiled program ready for use.
    ///
    /// @returns True if linking was successful or false if an error occured.
    ////////////////////////////////////////////////////////////////////////
    // Function:
    //
    // Description:
    //
    // Parameters:
    //
    // Returns:
    //
    ////////////////////////////////////////////////////////////////////////
    bool linkProgram(void);

    /// This function will make the ShaderProgram the active program.
    ////////////////////////////////////////////////////////////////////////
    // Function:
    //
    // Description:
    //
    // Parameters:
    //
    // Returns:
    //
    ////////////////////////////////////////////////////////////////////////
    void use(void);

    /// This function is a getter for mProgram.
    ////////////////////////////////////////////////////////////////////////
    // Function:
    //
    // Description:
    //
    // Parameters:
    //
    // Returns:
    //
    ////////////////////////////////////////////////////////////////////////
    GLint getProgram(void);

    /// The function retrieves a uniform location in the program.
    ////////////////////////////////////////////////////////////////////////
    // Function:
    //
    // Description:
    //
    // Parameters:
    //
    // Returns:
    //
    ////////////////////////////////////////////////////////////////////////
    GLuint getUniformLocation(std::string uniform);

    /// Copies the contents of one shader program to another.
    ////////////////////////////////////////////////////////////////////////
    // Function:
    //
    // Description:
    //
    // Parameters:
    //
    // Returns:
    //
    ////////////////////////////////////////////////////////////////////////
    ShaderProgram& operator=(const ShaderProgram& other);

private:
    /// @brief A flag indicating a complete program was created.
    bool mCompiledAndLinked;

    /// @brief The file used to compile the Vertex Shader.
    std::string mVertexFile;

    /// @brief The Vertex Shader source.
    std::string mVertexSource;

    /// @brief The OpenGL Compiled Vertex Shader.
    GLint mVertexShader;

    /// @brief The file used to compile the Fragment Shader.
    std::string mFragmentFile;

    /// @brief The Fragment Shader source.
    std::string mFragmentSource;

    /// @brief The OpenGL Compiled Fragment Shader.
    GLint mFragmentShader;

    /// @brief The OpenGL Linked Shader Program.
    GLint mProgram;

    /// @brief A helper function to read the contents of a file.
    ///
    /// This function reads the contents of the file passed in as an argument
    /// and returns the contents of that file as a string.
    ///
    /// @returns The contents of filename.
    ////////////////////////////////////////////////////////////////////////
    // Function:
    //
    // Description:
    //
    // Parameters:
    //
    // Returns:
    //
    ////////////////////////////////////////////////////////////////////////
    std::string readFile(std::string filename);

    /// @brief Prints the OpenGL Log when an error is detected.
    ///
    /// This function will print the contents of the OpenGL Info Log when
    /// something bad has happened.
    ////////////////////////////////////////////////////////////////////////
    // Function:
    //
    // Description:
    //
    // Parameters:
    //
    // Returns:
    //
    ////////////////////////////////////////////////////////////////////////
    void printInfoLog(GLint object);
};

#endif
