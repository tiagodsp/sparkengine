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
    OpenGLShader(const std::string &vertexSource, const std::string &fragmentSource);
    ~OpenGLShader();

    virtual void Bind() const override;
    virtual void Unbind() const override;

    // Float Uniforms -----------------
    virtual void UploadUniformFloat(const std::string &name, float f);
    virtual void UploadUniformFloat3(const std::string &name, const glm::vec2 &vector);
    virtual void UploadUniformFloat2(const std::string &name, const glm::vec3 &vector);
    virtual void UploadUniformFloat4(const std::string &name, const glm::vec4 &vector);

    // Matrix uniforms -----------------
    virtual void UploadUniformMat3(const std::string &name, const glm::mat3 &matrix);
    virtual void UploadUniformMat4(const std::string &name, const glm::mat4 &matrix);

private:
    GLuint m_RendererID;
};
} // namespace Spark
