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
/// This file contains the GLSL shader class. It is responsible for loading,
/// compiling, and attaching shaders. Each instance of this class contains one
/// vertex shader and one fragment shader.
////////////////////////////////////////////////////////////////////////////////
#ifndef SOURCE_CORE_SHADERS_SHADERPROGRAM_H_
#define SOURCE_CORE_SHADERS_SHADERPROGRAM_H_

// STL Includes.
#include <string>

// OpenGL Includes/
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class ShaderProgram
{
    public:
        ////////////////////////////////////////////////////////////////////////
        // Function:
        //    ShaderProgram
        // Description:
        //    At construction time, the files representing the vertex and
        //    fragment shaders are read in and compiled and a Program is made
        //    and linked. if any error occurs here, an ApplicationException is
        //    thrown.
        // Parameters:
        //
        // Returns:
        //
        ////////////////////////////////////////////////////////////////////////
        ShaderProgram(std::string argVertex, std::string argFragment);

        ////////////////////////////////////////////////////////////////////////
        // Function:
        //    ShaderProgram
        // Description:
        // This creates an empty Shader Program. It is unable to be used until a
        // vertex and fragment shader are added to it and a program is made via
        // the linkProgram method.
        // Parameters:
        //    None.
        // Returns:
        //    None.
        ////////////////////////////////////////////////////////////////////////
        ShaderProgram(void);

        ////////////////////////////////////////////////////////////////////////
        // Function:
        //    ~ShaderProgram
        // Description:
        //     This will free the OpenGL resources.
        // Parameters:
        //    None.
        // Returns:
        //    None.
        ////////////////////////////////////////////////////////////////////////
        ~ShaderProgram(void);

        ////////////////////////////////////////////////////////////////////////
        // Function:
        //    isReadyToUse
        // Description:
        //  A Program is ready to be used if it has been compiled and linked,
        //  which is the status of the mCompiledAndLinked member variable.
        // Parameters:
        //    None.
        // Returns:
        //    True if the program has been compiled and linked or false if it
        //  has not been either compiled or linked.
        ////////////////////////////////////////////////////////////////////////
        bool isReadyToUse(void);

        ////////////////////////////////////////////////////////////////////////
        // Function:
        //    useVertexShader
        // Description:
        //    This function will read the source of the file 'vertex' and
        //    compile it. Only one vertex shader can be associated with the
        //    shader program. If a previous vertex shader has been created,
        //    then it will be overwritten by the new one. Creating a new shader
        //    requires the program to be relinked.
        // Parameters:
        //    argVertex: Vertex shader path.
        // Returns:
        //    True if creation and compilation was successful or false if an
        //    error occured
        ////////////////////////////////////////////////////////////////////////
        bool useVertexShader(std::string argVertex);

        ////////////////////////////////////////////////////////////////////////
        // Function:
        //    useFragmentShader
        // Description:
        //    This function will read the source of the file 'fragment' and
        //  compile it. Only one fragment shader can be associated with the
        //  shader program. If a previous fragment shader has been created, then
        //  it will be overwritten by the new one. Creating a new shader
        //  requires the program to be relinked.
        // Parameters:
        //    argFragment: Fragment shader path.
        // Returns:
        //    True if creation and compilation was successful or false if an
        // error occured
        ////////////////////////////////////////////////////////////////////////
        bool useFragmentShader(std::string argFragment);

        ////////////////////////////////////////////////////////////////////////
        // Function:
        //    linkProgram
        // Description:
        //    This function will attach the fragment and vertex shader and link
        //    it into a compiled program ready for use.
        // Parameters:
        //    None.
        // Returns:
        //    True if linking was successful or false if an error occured.
        ////////////////////////////////////////////////////////////////////////
        bool linkProgram(void);

        ////////////////////////////////////////////////////////////////////////
        // Function:
        //    use
        // Description:
        //    This function will make the ShaderProgram the active program.
        // Parameters:
        //    None.
        // Returns:
        //    None.
        ////////////////////////////////////////////////////////////////////////
        void use(void);

        ////////////////////////////////////////////////////////////////////////
        // Function:
        //    program
        // Description:
        //    Getter for _program.
        // Parameters:
        //    None.
        // Returns:
        //    GLuint shader program.
        ////////////////////////////////////////////////////////////////////////
        GLuint program(void);

        /// The function retrieves a uniform location in the program.
        ////////////////////////////////////////////////////////////////////////
        // Function:
        //    uniformLocation
        // Description:
        //    The function retrieves a uniform location in the program.
        // Parameters:
        //    argUniform: Which uniform to get.
        // Returns:
        //    GLuint uniform id.
        ////////////////////////////////////////////////////////////////////////
        GLuint uniformLocation(std::string argUniform);

        ////////////////////////////////////////////////////////////////////////
        // Function:
        //    operator=
        // Description:
        //    Copies the contents of one shader program to another.
        // Parameters:
        //    argOther: ShaderProgram to copy.
        // Returns:
        //    ShaderProgram.
        ////////////////////////////////////////////////////////////////////////
        ShaderProgram& operator=(const ShaderProgram& argOther);

    private:
        // A flag indicating a complete program was created.
        bool _compiledAndLinked;

        // The file used to compile the Vertex Shader.
        std::string _vertexFile;

        // The Vertex Shader source.
        std::string _vertexSource;

        // The OpenGL Compiled Vertex Shader.
        GLuint _vertexShader;

        // The file used to compile the Fragment Shader.
        std::string _fragmentFile;

        // The Fragment Shader source.
        std::string _fragmentSource;

        // The OpenGL Compiled Fragment Shader.
        GLuint _fragmentShader;

        // The OpenGL Linked Shader Program.
        GLuint _program;

        ////////////////////////////////////////////////////////////////////////
        // Function:
        //    readFile
        // Description:
        //    This function reads the contents of the file passed in as an
        //    argument and returns the contents of that file as a string.
        // Parameters:
        //    argFilename: File to read.
        // Returns:
        //    The contents of the file.
        ////////////////////////////////////////////////////////////////////////
        std::string readFile(std::string argFilename);

        ////////////////////////////////////////////////////////////////////////
        // Function:
        //    printInfoLog
        // Description:
        //     This function will print the contents of the OpenGL Info Log when
        //     something bad has happened.
        // Parameters:
        //    argObject: OpenGL shader program.
        // Returns:
        //    None.
        ////////////////////////////////////////////////////////////////////////
        void printInfoLog(GLuint argObject);
};

#endif // SOURCE_CORE_SHADERS_SHADERPROGRAM_H_
