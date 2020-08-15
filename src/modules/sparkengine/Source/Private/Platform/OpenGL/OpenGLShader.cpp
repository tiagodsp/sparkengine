#include "sparkengine.PCH.h"
#include "OpenGLShader.h"

#include <fstream>
#include <regex>
#include "glm/gtc/type_ptr.hpp"
#include "glad/glad.h"


namespace Spark
{

static GLenum ShaderTypeFromString(std::string shadertype)
{
    if(shadertype == "vertex")
    {
        return GL_VERTEX_SHADER;
    }
    else if (shadertype == "fragment")
    {
        return GL_FRAGMENT_SHADER;
    }
    else
    {
        return 0;
    }
}


OpenGLShader::OpenGLShader(const std::string &filepath)
{
    std::string shaderSource = ReadFile(filepath);
    Compile(PreProcess(shaderSource));
}

OpenGLShader::OpenGLShader(const std::string &vertexSource, const std::string &fragmentSource)
{
    std::unordered_map<GLenum, std::string> sourceShaders;
    sourceShaders.insert({GL_VERTEX_SHADER , vertexSource});
    sourceShaders.insert({GL_FRAGMENT_SHADER , fragmentSource});
    Compile(sourceShaders);
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
    std::ifstream in(filepath, std::ios::in | std::ios::binary);
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
        GLenum type = ShaderTypeFromString(matchs[1]);
        CORE_ASSERT(type, "Shader type not supported.");
        std::string source = matchs[2];
        shaderSources.insert_or_assign(type, source);
        itr = matchs[0].second;
    }
    return shaderSources;
}

void OpenGLShader::Compile(std::unordered_map<GLenum, std::string> sourceShaders)
{
    CORE_ASSERT(sourceShaders.size() > 2, "OpenGLShader::Compile function only supports up to 2 shaders.");
    std::array<GLint, 2> shaders;
    int currentShaderIndex = 0;
    
    for(auto ss : sourceShaders)
    {
        GLenum type = ss.first;
        std::string source = ss.second;

        // Create an empty handle
        GLuint shader = glCreateShader(type);
        shaders[currentShaderIndex++] = shader;

        // Send the shader source code to GL        
        const GLchar *source_cstr = (const GLchar *)source.c_str();
        glShaderSource(shader, 1, &source_cstr, 0);

        // Compile the shader
        glCompileShader(shader);

        GLint isCompiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);

        if (isCompiled == GL_FALSE)
        {
            GLint logLength = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> infoLog(logLength);
            glGetShaderInfoLog(shader, logLength, &logLength, &infoLog[0]);

            // We don't need the shader anymore.
            glDeleteShader(shader);

            // Use the infoLog as you see fit.
            CORE_LOGF("Shader compilation failure!");
            CORE_LOGF("{0}", infoLog.data());
            CORE_ASSERT(false, "Shader compilation failure!");
            return;
        }
    }
    
    // Shaders are successfully compiled.
    // Now time to link them together into a program.
    // Get a program object.
    GLuint program = glCreateProgram();

    // Attach our shaders to our program
    for(auto s : shaders)
        glAttachShader(program, s);

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
        for(auto s : shaders)
            glDeleteShader(s);

        // Use the infoLog as you see fit.

        // In this simple program, we'll just leave
        CORE_LOGF("{0}", infoLog.data());
        CORE_ASSERT(false, "Shader link failure!");
        return;
    }

    // Always detach shaders after a successful link.
    for(auto s : shaders)
        glDetachShader(program, s);

    // If everthing was built successfuly, save Renderer ID;
    m_RendererID = program;
}


} // namespace Spark