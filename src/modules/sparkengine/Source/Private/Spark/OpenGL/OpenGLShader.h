#pragma once
#include "Spark/Renderer/IShader.h"
#include "glad/glad.h"

namespace Spark
{
/**
 * OpenGL Shader implementation
 */
class OpenGLShader final : public IShader
{
public:
    OpenGLShader(const std::string &filepath);
    OpenGLShader(const std::string &name, const std::string &vertexSource, const std::string &fragmentSource);
    
    ~OpenGLShader();

    virtual void Bind() const override;
    virtual void Unbind() const override;

    virtual const std::string &GetName() const override { return m_Name; };

    // Float Uniforms -----------------
    virtual void UploadUniformFloat(const std::string &name, float f) override;
    virtual void UploadUniformFloat3(const std::string &name, const glm::vec2 &vector) override;
    virtual void UploadUniformFloat2(const std::string &name, const glm::vec3 &vector) override;
    virtual void UploadUniformFloat4(const std::string &name, const glm::vec4 &vector) override;

    // Interger uniforms -----------------
    virtual void UploadUniformInt(const std::string &name, int i) override;

    // Matrix uniforms -----------------
    virtual void UploadUniformMat3(const std::string &name, const glm::mat3 &matrix) override;
    virtual void UploadUniformMat4(const std::string &name, const glm::mat4 &matrix) override;

private:
    std::string ReadFile(const std::string& filepath);
    std::unordered_map<GLenum, std::string> PreProcess(const std::string& filepath);
    void Compile(std::unordered_map<GLenum, std::string> sourceShaders);

private:
    GLuint m_RendererID;
    std::string m_Name;
};
} // namespace Spark
