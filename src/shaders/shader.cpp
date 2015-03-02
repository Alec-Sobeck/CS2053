
#include <iostream>
#include <stdexcept>
#include <glbinding/gl/gl.h>
#include "utils/fileutils.h"
#include "shaders/shader.h"

void _printShaderInfoLog(GLuint obj);
void _printProgramInfoLog(GLuint obj);

Shader::Shader(GLuint programID)
{
    this->programID = programID;
}

void Shader::bindShader()
{
    glUseProgramObjectARB(programID);
}

void Shader::releaseShader()
{
    glUseProgramObjectARB(0);
}

void Shader::glUniform1(std::string attributeName, GLfloat v)
{
    glUseProgram(programID);
    ::glUniform1f(glGetUniformLocation(programID, attributeName.c_str()), v);
}

void Shader::glUniform1(std::string attributeName, GLint v)
{
    glUseProgram(programID);
    glUniform1i(glGetUniformLocation(programID, attributeName.c_str()), v);
}

void Shader::glUniform1(std::string attributeName, bool v)
{
    glUseProgram(programID);
    glUniform1i(glGetUniformLocation(programID, attributeName.c_str()), v);
}

void Shader::glUniform2(std::string attributeName, GLfloat v0, GLfloat v1)
{
    glUseProgram(programID);
    glUniform2f(glGetUniformLocation(programID, attributeName.c_str()), v0, v1);
}

void Shader::glUniform2(std::string attributeName, glm::vec2 v)
{
    glUseProgram(programID);
    glUniform2f(glGetUniformLocation(programID, attributeName.c_str()), v.x, v.y);
}

void Shader::glUniform2(std::string attributeName, GLint v0, GLint v1)
{
    glUseProgram(programID);
    glUniform2i(glGetUniformLocation(programID, attributeName.c_str()), v0, v1);
}

void Shader::glUniform3(std::string attributeName, GLfloat v0, GLfloat v1, GLfloat v2)
{
    glUseProgram(programID);
    glUniform3f(glGetUniformLocation(programID, attributeName.c_str()), v0, v1, v2);
}

void Shader::glUniform3(std::string attributeName, glm::vec3 v)
{
    glUseProgram(programID);
    glUniform3f(glGetUniformLocation(programID, attributeName.c_str()), v.x, v.y, v.z);
}

void Shader::glUniform3(std::string attributeName, GLint v0, GLint v1, GLint v2)
{
    glUseProgram(programID);
    glUniform3i(glGetUniformLocation(programID, attributeName.c_str()), v0, v1, v2);
}

void Shader::glUniform4(std::string attributeName, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
{
    glUseProgram(programID);
    glUniform4f(glGetUniformLocation(programID, attributeName.c_str()), v0, v1, v2, v3);
}

void Shader::glUniform4(std::string attributeName, glm::vec4 v)
{
    glUseProgram(programID);
    glUniform4f(glGetUniformLocation(programID, attributeName.c_str()), v.x, v.y, v.z, v.w);
}

void Shader::glUniform4(std::string attributeName, GLint v0, GLint v1, GLint v2, GLint v3)
{
    glUseProgram(programID);
    glUniform4i(glGetUniformLocation(programID, attributeName.c_str()), v0, v1, v2, v3);
}
/*
void Shader::glUniformMatrix2(std::string attributeName, boolean transpose, java.nio.FloatBuffer matrices)
{
    glUseProgram(programID);
    glUniformMatrix2(glGetUniformLocation(programID, attributeName), transpose, matrices);
}

void Shader::glUniformMatrix3(std::string attributeName, boolean transpose, java.nio.FloatBuffer matrices)
{
    glUseProgram(programID);
    glUniformMatrix3(glGetUniformLocation(programID, attributeName), transpose, matrices);
}

void Shader::glUniformMatrix4(std::string attributeName, boolean transpose, java.nio.FloatBuffer matrices)
{
    glUseProgram(programID);
    glUniformMatrix4(glGetUniformLocation(programID, attributeName), transpose, matrices);
}
*/

void Shader::printShaderInfoLog()
{
    GLuint obj = static_cast<GLuint>(this->programID);
    _printShaderInfoLog(obj);
}

void Shader::printProgramInfoLog()
{
    GLuint obj = static_cast<GLuint>(this->programID);
    _printProgramInfoLog(obj);
}

//***********************************************************************************************************************************
//***********************************************************************************************************************************
//***      Declare functions which create/load shaders or do other helpful things. These might not be part of the public API.     ***
//***********************************************************************************************************************************
//***********************************************************************************************************************************

void _printShaderInfoLog(GLuint obj)
{
    int infologLength = 0;
    int charsWritten  = 0;
    char *infoLog;

    glGetShaderiv(obj, GL_INFO_LOG_LENGTH, &infologLength);

    if (infologLength > 0)
    {
        infoLog = (char *)malloc(infologLength);
        glGetShaderInfoLog(obj, infologLength, &charsWritten, infoLog);
        printf("%s\n",infoLog);
        free(infoLog);
    }
}

void _printProgramInfoLog(GLuint obj)
{
    int infologLength = 0;
    int charsWritten  = 0;
    char *infoLog;

    glGetProgramiv(obj, GL_INFO_LOG_LENGTH,&infologLength);

    if (infologLength > 0)
    {
        infoLog = (char *)malloc(infologLength);
        glGetProgramInfoLog(obj, infologLength, &charsWritten, infoLog);
        printf("%s\n",infoLog);
        free(infoLog);
    }
}

/**
 * Creates an OpenGL shader.
 * @param filename a String which has the filepath to the GLSL shader file to use
 * @param shaderType the type of the shader to use - either GL_FRAGMENT_SHADER_ARB or GL_VERTEX_SHADER_ARB depending on the shader type
 * @return an GLuint which uniquely identifies this shader within the program.
 */
int createShader(std::string filename, GLenum shaderType)
{
    GLint shader = 0;
    try
    {
        shader = glCreateShader(shaderType);
        if(shader == 0)
        {
            return 0;
        }

        std::string fileContents = readTextFile(filename);
        glShaderSourceARB(shader, 1, (const GLcharARB**)fileContents.c_str(), nullptr);
        glCompileShaderARB(shader);
        GLint ret = 0;
        glGetObjectParameterivARB(shader, GL_OBJECT_COMPILE_STATUS_ARB, &ret);
        if (ret == 0)
        {
            std::cout << "Error creating shader: " << std::endl << "Program Info Log:" << std::endl;
            _printProgramInfoLog(shader);
            std::cout << std::endl << "Shader Info Log: " << std::endl;
            _printShaderInfoLog(shader);
            return -1;
        }
        return shader;
    }
    catch(std::runtime_error &exc)
    {
        glDeleteObjectARB(shader);
        return -1;
    }
}

/**
 * Attempts to create a shader. This may have either a vertex shader part, fragment shader part, or both.
 * @param vertFilepath a String which has the filepath of the source code to use for the vertex shader, or
 * null if no vertex shader is to be used.
 * @param fragFilepath a String which has the filepath of the source code to use for the fragment shader,
 * or null if no fragment shader is to be used.
 * @return a Shader object with no variables assigned any values, or null if shader creation fails.
 */
std::shared_ptr<Shader> createShader(const std::string *vertFilepath, const std::string *fragFilepath)
{
    int program = -1;
    int vertShader = -1;
    int fragShader = -1;
    if(vertFilepath != nullptr)
    {
        vertShader = createShader((*vertFilepath), GL_VERTEX_SHADER_ARB);
    }
    if(fragFilepath != nullptr)
    {
        fragShader = createShader((*fragFilepath), GL_FRAGMENT_SHADER_ARB);
    }

    // Failure case - couldn't create the shader
    if((vertFilepath != nullptr && vertShader == -1) || (fragFilepath != nullptr && fragShader == -1))
    {
        return std::shared_ptr<Shader>(nullptr);
    }

    program = glCreateProgramObjectARB();
    if(program == 0)
    {
        return nullptr;
    }

    if(vertFilepath != nullptr)
    {
        glAttachObjectARB(program, vertShader);
    }
    if(fragFilepath != nullptr)
    {
        glAttachObjectARB(program, fragShader);
    }

    glLinkProgramARB(program);
    GLint ret = 0;
    glGetObjectParameterivARB(program, GL_OBJECT_LINK_STATUS_ARB, &ret);
    if (ret == 0)
    {
        std::cout << "Error creating shader: " << std::endl << "Program Info Log:" << std::endl;
        _printProgramInfoLog(program);
        std::cout << std::endl << "Shader Info Log: " << std::endl;
        _printShaderInfoLog(program);
        return std::shared_ptr<Shader>(nullptr);
    }

    glValidateProgramARB(program);
    glGetObjectParameterivARB(program, GL_OBJECT_VALIDATE_STATUS_ARB, &ret);
    if (ret == 0)
    {
        std::cout << "Error creating shader: " << std::endl << "Program Info Log:" << std::endl;
        _printProgramInfoLog(program);
        std::cout << std::endl << "Shader Info Log: " << std::endl;
        _printShaderInfoLog(program);
        return std::shared_ptr<Shader>(nullptr);
    }
    return std::shared_ptr<Shader>(new Shader(program));
}




