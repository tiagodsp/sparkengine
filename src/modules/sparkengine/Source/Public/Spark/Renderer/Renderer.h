#pragma once

#include "Spark/Renderer/PlatformRendererAPI.h"
#include "Spark/Renderer/IVertexArray.h"
#include "Spark/Renderer/OrthographicCamera.h"
#include "Spark/Renderer/IShader.h"
#include "sparkengine.api.gen.h"

namespace Spark
{

class SPARKENGINE_API  Renderer
{
public:
    static void BeginScene(OrthographicCamera& camera);
    static void EndScene();

    static void Submit(const std::shared_ptr<IShader>& shader, const std::shared_ptr<IVertexArray>& vertexArray);

    inline static PlatformRendererAPI::API GetAPI() {return  PlatformRendererAPI::GetAPI(); }
private:
    struct SceneData
    {
        glm::mat4 ViewProjectionMatrix;
    };

    static SceneData* s_SceneData;
};


} // namespace Spark
