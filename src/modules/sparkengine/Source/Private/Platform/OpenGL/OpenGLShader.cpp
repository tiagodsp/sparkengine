#include "sparkengine.PCH.h"
#include "OpenGLShader.h"

#include <fstream>
#include <regex>
#include "glm/gtc/type_ptr.hpp"
#include "glad/glad.h"


namespace Spark
{

OpenGLShader::OpenGLShader(const std::string &filepath)
{
    std::string shaderSource = ReadFile(filepath);
    PreProcess(shaderSource);
}

OpenGLShader::OpenGLShader(const std::string &vertexSource, const std::string &fragmentSource)
{
    // Create an empty vertex shader handle
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

    // Send the vertex shader source code to GL
    // Note that std::string's .c_str is NULL character terminated.
    const GLchar *source = (const GLchar *)vertexSource.c_str();
    glShaderSource(vertexShader, 1, &source, 0);

    // Compile the vertex shader
    glCompileShader(vertexShader);

    GLint isCompiled = 0;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

        // We don't need the shader anymore.
        glDeleteShader(vertexShader);

        // Use the infoLog as you see fit.
        CORE_LOGF("Vertex Shader compilation failure!");
        CORE_LOGF("{0}", infoLog.data());
        CORE_ASSERT(false, "Vertex Shader compilation failure!");
        return;
    }

    // Create an empty fragment shader handle
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    // Send the fragment shader source code to GL
    // Note that std::string's .c_str is NULL character terminated.
    source = (const GLchar *)fragmentSource.c_str();
    glShaderSource(fragmentShader, 1, &source, 0);

    // Compile the fragment shader
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

        // We don't need the shader anymore.
        glDeleteShader(fragmentShader);
        // Either of them. Don't leak shaders.
        glDeleteShader(vertexShader);

        // Use the infoLog as you see fit.
        CORE_LOGF("Fragment Shader compilation failure!");
        CORE_LOGF("{0}", infoLog.data());
        CORE_ASSERT(false, "Fragment Shader compilation failure!");
        return;
    }

    // Vertex and fragment shaders are successfully compiled.
    // Now time to link them together into a program.
    // Get a program object.
    m_RendererID = glCreateProgram();
    GLuint program = m_RendererID;

    // Attach our shaders to our program
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    // Link our program
    glLinkProgram(program);

    // Note the different functions here: glGetProgram* instead of glGetShader*.
    GLint isLinked = 0;
    glGetProgramiv(program, GL_LINK_STATUS, (int *)&isLinked);
    if (isLinked == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

        // We don't need the program anymore.
        glDeleteProgram(program);
        // Don't leak shaders either.
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        // Use the infoLog as you see fit.

        // In this simple program, we'll just leave
        CORE_LOGF("{0}", infoLog.data());
        CORE_ASSERT(false, "Shader link failure!");
        return;
    }

    // Always detach shaders after a successful link.
    glDetachShader(program, vertexShader);
    glDetachShader(program, fragmentShader);
}

OpenGLShader::~OpenGLShader()
{
    glDeleteProgram(m_RendererID);
}

void OpenGLShader::Bind() const
{
    glUseProgram(m_RendererID);
}

void OpenGLShader::Unbind() const
{
    glUseProgram(0);
}

void OpenGLShader::UploadUniformFloat(const std::string &name, float f)
{
    GLint location = glGetUniformLocation(m_RendererID, name.c_str());
    glUniform1f(location, f);
}

void OpenGLShader::UploadUniformFloat3(const std::string &name, const glm::vec2 &vector)
{
    GLint location = glGetUniformLocation(m_RendererID, name.c_str());
    glUniform2fv(location, 1, glm::value_ptr(vector));
}

void OpenGLShader::UploadUniformFloat2(const std::string &name, const glm::vec3 &vector)
{
    GLint location = glGetUniformLocation(m_RendererID, name.c_str());
    glUniform3fv(location, 1, glm::value_ptr(vector));
}

void OpenGLShader::UploadUniformFloat4(const std::string &name, const glm::vec4 &vector)
{
    GLint location = glGetUniformLocation(m_RendererID, name.c_str());
    glUniform4fv(location, 1, glm::value_ptr(vector));
}

void OpenGLShader::UploadUniformInt(const std::string &name, int i)
{
    GLint location = glGetUniformLocation(m_RendererID, name.c_str());
    glUniform1i(location, i);
}

void OpenGLShader::UploadUniformMat3(const std::string &name, const glm::mat3 &matrix)
{
    GLint location = glGetUniformLocation(m_RendererID, name.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void OpenGLShader::UploadUniformMat4(const std::string &name, const glm::mat4 &matrix)
{
    GLint location = glGetUniformLocation(m_RendererID, name.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}


std::string OpenGLShader::ReadFile(const std::string& filepath)
{
    std::string result;
    std::ifstream in(filepath, std::ios::in, std::ios::binary);
    if(in)
    {
        in.seekg(0, std::ios::end);
        result.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&result[0],result.size());
        in.close();
    }
    else
    {
        CORE_LOGE("Could not open file {0}", filepath);
    }
    return result;
}

std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string& filedata)
{
    std::unordered_map<GLenum, std::string> shaderSources;

    //std::regex regex(R"(#type[ ]+([a-zA-Z0-9]+)[\r\n]+((.+?)[\r\n]*(?=#type|\Z)))");
    std::regex regex(R"(#type[ ]+([a-zA-Z0-9]+)[\s]+([\S\s]*?(?=#type|(?!(.|\n))$)))", std::regex_constants::ECMAScript);
    std::smatch matchs;
    auto itr = filedata.begin();
    while(std::regex_search(itr, filedata.end(), matchs, regex))
    {
        for(auto m : matchs)
        {
            CORE_LOGI(m);
        }
        itr = matchs[0].second;
    }
    return shaderSources;
}

void OpenGLShader::Compile()
{

}


} // namespace Spark