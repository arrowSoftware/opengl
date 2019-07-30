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

#include "Cube.h"
#include "Utils.h"
#include "Application.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

constexpr GLfloat Cube::g_vertex_buffer_data[];
constexpr GLfloat Cube::g_color_buffer_data[];

Cube::Cube(std::string argObjectName) :
    Object(argObjectName)
{
}

Cube::~Cube(void)
{
}

void Cube::draw(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _shaderProgram.use();

    // Send our transformation to the currently bound shader,
    // in the "MVP" uniform
    glUniformMatrix4fv((GLint)MatrixID, 1, GL_FALSE, &MVP[0][0]);

    glPushMatrix();
    glPushAttrib(GL_ALL_ATTRIB_BITS);

    // 1st attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
        0,                          // attribute 0. No particular reason for 0,
                                    // but must match the layout in the shader.
        3,                          // size
        GL_FLOAT,                   // type
        GL_FALSE,                   // normalized?
        0,                          // stride
        reinterpret_cast<void*>(0)); // array buffer offset

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glVertexAttribPointer(
        1,                          // attribute. No particular reason for 1,
                                    // but must match the layout in the shader.
        3,                          // size
        GL_FLOAT,                   // type
        GL_FALSE,                   // normalized?
        0,                          // stride
        reinterpret_cast<void*>(0)); // array buffer offset

    // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0, 12 * 3);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    glPopAttrib();
    glPopMatrix();
}

void Cube::initialize(void)
{
    glGenVertexArrays(1, &VertexArrayID);
        glBindVertexArray(VertexArrayID);

        // Get a handle for our "MVP" uniform
        MatrixID = glGetUniformLocation(_shaderProgram.program(), "MVP");

        // Projection matrix : 45° Field of View, 4:3 ratio, display
        // range : 0.1 unit <-> 100 units
        Projection = glm::perspective(glm::radians(45.0f),
                                      4.0f / 3.0f,
                                      0.1f,
                                      100.0f);

        // Camera matrix
        View = glm::lookAt(
            glm::vec3(4, 3, -3), // Camera is at (4,3,-3), in World Space
            glm::vec3(0, 0, 0),  // and looks at the origin
            glm::vec3(0, 1, 0)); // Head is up (set to 0,-1,0 to look
                                 // upside-down)

        // Model matrix : an identity matrix (model will be at the origin)
        Model = glm::mat4(1.0f);

        // Our ModelViewProjection : multiplication of our 3 matrices
        // Remember, matrix multiplication is the other way around.
        MVP = Projection * View * Model;

        // Generate 1 buffer, put the resulting identifier in vertexbuffer
        glGenBuffers(1, &vertexbuffer);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glBufferData(GL_ARRAY_BUFFER,
                     sizeof(g_vertex_buffer_data),
                     g_vertex_buffer_data,
                     GL_STATIC_DRAW);

        // The following commands will talk about our 'vertexbuffer' buffer
        glGenBuffers(1, &colorbuffer);
        glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
        glBufferData(GL_ARRAY_BUFFER,
                     sizeof(g_color_buffer_data),
                     g_color_buffer_data,
                     GL_STATIC_DRAW);
}

void Cube::wrapup(void)
{
    // Cleanup VBO and shader
    glDeleteBuffers(1, &vertexbuffer);
    glDeleteBuffers(1, &colorbuffer);
    glDeleteProgram(_shaderProgram.program());
    glDeleteVertexArrays(1, &VertexArrayID);
}
