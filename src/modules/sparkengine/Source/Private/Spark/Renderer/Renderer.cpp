#include "sparkengine.PCH.h"
#include "Spark/Renderer/RenderCommand.h"
#include "Spark/Renderer/Renderer.h"
#include "Spark/Renderer/Renderer2D.h"

namespace Spark
{

    Renderer::SceneData *Renderer::s_SceneData = new Renderer::SceneData();

    void Renderer::Init()
    {
        RenderCommand::Init();
        Renderer2D::Init();
    }

    void Renderer::Shutdown()
    {

    }

    void Renderer::BeginScene(Camera &camera)
    {
        s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatix();
    }
    void Renderer::EndScene()
    {
        RenderCommand::Commit();
    }

    void Renderer::Submit(const Ref<IShader> &shader, const Ref<IVertexArray> &vertexArray, const glm::mat4 &transform)
    {
        shader->UploadUniformMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
        shader->UploadUniformMat4("u_Transform", transform);
        shader->Bind();

        vertexArray->Bind();
        RenderCommand::DrawIndexed(vertexArray);
        vertexArray->Unbind();

        shader->Unbind();
    }

    void Renderer::OnWindowResize(uint32 Width, uint32 Height)
    {
        RenderCommand::SetViewport(0, 0, Width, Height);
    }

    Ref<IGraphicsContext> Renderer::GetGraphicsContext()
    {
        return RenderCommand::GetGraphicsContext();
    }

    void Renderer::SetGraphicsContext(Ref<IGraphicsContext> context)
    {
        RenderCommand::SetGraphicsContext(context);
    }

    Ref<PlatformRendererAPI> Renderer::GetLowLevelAPI()
    {
        return RenderCommand::s_RendererAPI;
    }

} // namespace Spark
