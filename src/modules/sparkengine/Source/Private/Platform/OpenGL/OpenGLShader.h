#pragma once
#include "Spark/Renderer/IShader.h"
#include "glad/glad.h"

namespace Spark
{
class OpenGLShader : public IShader
{
public:
    OpenGLShader(const std::string &vertexSource, const std::string &fragmentSource);
    ~OpenGLShader();

    virtual void Bind() const override;
    virtual void Unbind() const override;

private:
    GLuint m_RendererID;
};
} // namespace Spark
