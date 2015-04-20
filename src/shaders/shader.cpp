
#include <iostream>
#include <stdexcept>
#include "utils/fileutils.h"
#include "shaders/shader.h"

void _printShaderInfoLog(gl::GLuint obj);
void _printProgramInfoLog(gl::GLuint obj);

Shader::Shader(gl::GLhandleARB programID) : programID(programID)
{
    std::cout << "CREATE_SHADER:" << programID << std::endl;
}

void Shader::bindShader()
{
    gl::glUseProgramObjectARB(programID);
}

void Shader::releaseShader()
{
    gl::glUseProgramObjectARB(0);
}

void Shader::glUniform1(std::string attributeName, gl::GLfloat v)
{
    gl::glUseProgram(programID);
    gl::glUniform1f(gl::glGetUniformLocation(programID, attributeName.c_str()), v);
}

void Shader::glUniform1(std::string attributeName, gl::GLint v)
{
    gl::glUseProgram(programID);
    gl::glUniform1i(gl::glGetUniformLocation(programID, attributeName.c_str()), v);
}

void Shader::glUniform1(std::string attributeName, bool v)
{
    gl::glUseProgram(programID);
    gl::glUniform1i(gl::glGetUniformLocation(programID, attributeName.c_str()), v);
}

void Shader::glUniform2(std::string attributeName, gl::GLfloat v0, gl::GLfloat v1)
{
    gl::glUseProgram(programID);
    gl::glUniform2f(gl::glGetUniformLocation(programID, attributeName.c_str()), v0, v1);
}

void Shader::glUniform2(std::string attributeName, glm::vec2 v)
{
    gl::glUseProgram(programID);
    gl::glUniform2f(gl::glGetUniformLocation(programID, attributeName.c_str()), v.x, v.y);
}

void Shader::glUniform2(std::string attributeName, gl::GLint v0, gl::GLint v1)
{
    gl::glUseProgram(programID);
    gl::glUniform2i(gl::glGetUniformLocation(programID, attributeName.c_str()), v0, v1);
}

void Shader::glUniform3(std::string attributeName, gl::GLfloat v0, gl::GLfloat v1, gl::GLfloat v2)
{
    gl::glUseProgram(programID);
    gl::glUniform3f(gl::glGetUniformLocation(programID, attributeName.c_str()), v0, v1, v2);
}

void Shader::glUniform3(std::string attributeName, glm::vec3 v)
{
    gl::glUseProgram(programID);
    gl::glUniform3f(gl::glGetUniformLocation(programID, attributeName.c_str()), v.x, v.y, v.z);
}

void Shader::glUniform3(std::string attributeName, gl::GLint v0, gl::GLint v1, gl::GLint v2)
{
    gl::glUseProgram(programID);
    gl::glUniform3i(gl::glGetUniformLocation(programID, attributeName.c_str()), v0, v1, v2);
}

void Shader::glUniform4(std::string attributeName, gl::GLfloat v0, gl::GLfloat v1, gl::GLfloat v2, gl::GLfloat v3)
{
    gl::glUseProgram(programID);
    gl::glUniform4f(gl::glGetUniformLocation(programID, attributeName.c_str()), v0, v1, v2, v3);
}

void Shader::glUniform4(std::string attributeName, glm::vec4 &v)
{
    gl::glUseProgram(programID);
    gl::glUniform4f(gl::glGetUniformLocation(programID, attributeName.c_str()), v.x, v.y, v.z, v.w);
}

void Shader::glUniform4(std::string attributeName, gl::GLint v0, gl::GLint v1, gl::GLint v2, gl::GLint v3)
{
    gl::glUseProgram(programID);
    gl::glUniform4i(gl::glGetUniformLocation(programID, attributeName.c_str()), v0, v1, v2, v3);
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
    _printShaderInfoLog(this->programID);
}

void Shader::printProgramInfoLog()
{
    _printProgramInfoLog(this->programID);
}

//***********************************************************************************************************************************
//***********************************************************************************************************************************
//***      Declare functions which create/load shaders or do other helpful things. These might not be part of the public API.     ***
//***********************************************************************************************************************************
//***********************************************************************************************************************************

void _printShaderInfoLog(gl::GLuint obj)
{
    using namespace gl;
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

void _printProgramInfoLog(gl::GLuint obj)
{
    using namespace gl;
    int infologLength = 0;
    int charsWritten  = 0;
    char *infoLog;

    glGetProgramiv(obj, GL_INFO_LOG_LENGTH, &infologLength);

    if (infologLength > 0)
    {
        infoLog = (char *)malloc(infologLength);
        glGetProgramInfoLog(obj, infologLength, &charsWritten, infoLog);
        printf("%s\n",infoLog);
        free(infoLog);
    }
}

///
/// Creates an OpenGL shader.
/// \param filename a String which has the filepath to the GLSL shader file to use
/// \param shaderType the type of the shader to use - either GL_FRAGMENT_SHADER_ARB or GL_VERTEX_SHADER_ARB depending on the shader type
/// \return an gl::GLuint which uniquely identifies this shader within the program.
int createShader(const std::string *filename, gl::GLenum shaderType)
{
    using namespace gl;
    GLint shader = 0;
    try
    {
        shader = glCreateShader(shaderType);
        if(shader == 0)
        {
            return 0;
        }

        std::string fileContents = readTextFile((*filename));
        const char* val = fileContents.c_str();
        GLint len = static_cast<GLint>(fileContents.length());
        glShaderSourceARB(shader, 1, const_cast<const GLcharARB**>(&val), &len);
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

///
/// Attempts to create a shader. This may have either a vertex shader part, fragment shader part, or both.
/// \param vertFilepath a String which has the filepath of the source code to use for the vertex shader, or
/// nullptr if no vertex shader is to be used.
/// \param fragFilepath a String which has the filepath of the source code to use for the fragment shader,
/// or nullptr if no fragment shader is to be used.
/// \return a Shader object with no variables assigned any values, or null if shader creation fails.
///
std::shared_ptr<Shader> createShader(const std::string *vertFilepath, const std::string *fragFilepath)
{
    using namespace gl;
    int program = -1;
    int vertShader = -1;
    int fragShader = -1;
    if(vertFilepath)
    {
        vertShader = createShader(vertFilepath, GL_VERTEX_SHADER_ARB);
    }
    if(fragFilepath)
    {
        fragShader = createShader(fragFilepath, GL_FRAGMENT_SHADER_ARB);
    }

    // Failure case - couldn't create the shader
    if((vertFilepath && vertShader == -1) || (fragFilepath && fragShader == -1))
    {
        return std::shared_ptr<Shader>(nullptr);
    }

    program = glCreateProgramObjectARB();
    if(program == 0)
    {
        return std::shared_ptr<Shader>(nullptr);
    }

    if(vertFilepath)
    {
        glAttachObjectARB(program, vertShader);
    }
    if(fragFilepath)
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




