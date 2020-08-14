#pragma once

#include <memory>
#include "glm/glm.hpp"

#include "sparkengine.api.gen.h"

namespace Spark
{

class SPARKENGINE_API IShader
{
public:
    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;
    
    static Ref<IShader> Create(const std::string &filepath);
    static Ref<IShader> Create(const std::string &vertexSource, const std::string &fragmentSource);

    // Float Uniforms -----------------
    virtual void UploadUniformFloat(const std::string &name, float f) = 0;
    virtual void UploadUniformFloat3(const std::string &name, const glm::vec2 &vector) = 0;
    virtual void UploadUniformFloat2(const std::string &name, const glm::vec3 &vector) = 0;
    virtual void UploadUniformFloat4(const std::string &name, const glm::vec4 &vector) = 0;

    // Interger uniforms -----------------
    virtual void UploadUniformInt(const std::string &name, int i) = 0;

    // Matrix uniforms -----------------
    virtual void UploadUniformMat3(const std::string &name, const glm::mat3 &matrix) = 0;
    virtual void UploadUniformMat4(const std::string &name, const glm::mat4 &matrix) = 0;
};

} // namespace Spark