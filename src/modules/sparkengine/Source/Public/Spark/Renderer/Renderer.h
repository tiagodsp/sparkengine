#pragma once

#include "Spark/Renderer/PlatformRendererAPI.h"
#include "Spark/Renderer/IVertexArray.h"
#include "sparkengine.api.gen.h"

namespace Spark
{

class SPARKENGINE_API  Renderer
{
public:
    static void BeginScene();
    static void EndScene();

    static void Submit(const std::shared_ptr<IVertexArray>& vertexArray);

    inline static PlatformRendererAPI::API GetAPI() {return  PlatformRendererAPI::GetAPI(); }
};


} // namespace Spark
