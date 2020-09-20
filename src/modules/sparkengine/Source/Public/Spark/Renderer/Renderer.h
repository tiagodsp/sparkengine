#pragma once

#include "Spark/Renderer/PlatformRendererAPI.h"
#include "Spark/Renderer/IVertexArray.h"
#include "Spark/Renderer/Camera.h"
#include "Spark/Renderer/IShader.h"
#include "sparkengine.api.gen.h"

namespace Spark
{

class SPARKENGINE_API  Renderer
{
public:
    static void Init();
    static void Shutdown();

    static void BeginScene(Camera& camera);
    static void EndScene();

    static void Submit(const Ref<IShader>& shader, const Ref<IVertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));

    static void OnWindowResize(uint32 Width, uint32 Height);

    inline static PlatformRendererAPI::API GetAPI() {return  PlatformRendererAPI::GetAPI(); }
private:
    struct SceneData
    {
        glm::mat4 ViewProjectionMatrix;
    };

    static SceneData* s_SceneData;
};


} // namespace Spark
