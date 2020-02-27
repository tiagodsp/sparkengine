#pragma once

#include <memory>
#include "glm/glm.hpp"

#include "sparkengine.api.gen.h"

namespace Spark
{

class IShader
{
public:
    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;
    virtual void UploadUniformMat4(const std::string &name, const glm::mat4 &matrix) = 0;

    static std::shared_ptr<IShader> Create(const std::string &vertexSource, const std::string &fragmentSource);
};

} // namespace Spark