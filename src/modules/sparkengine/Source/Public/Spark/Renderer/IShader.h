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
    
    static Ref<IShader> Create(const std::string &vertexSource, const std::string &fragmentSource);
};

} // namespace Spark