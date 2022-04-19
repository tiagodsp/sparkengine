#include "Spark/Core/Input.h"
#include "sparkengine.PCH.h"
#include "Spark/Renderer/RenderCommand.h"
#include "Spark/Renderer/Renderer.h"
#include "Spark/Renderer/Renderer2D.h"
#include "Spark/Core/Platform.h"

// TODO - Create engine globals that can provide delta time and other stuff
static Spark::Timestep deltaTime = 0.0f;
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
        shader->UploadUniformFloat2("u_Resolution", glm::vec2(1280.0f, 720.0f));
        deltaTime = Platform::Get()->GetTime() - deltaTime;
        shader->UploadUniformFloat("u_Time", Platform::Get()->GetTime().GetTimeSeconds());
        shader->UploadUniformFloat("u_TimeDelta", deltaTime.GetTimeSeconds());
        shader->UploadUniformFloat2("u_MousePosition", glm::vec2(Input::GetMouseX(), Input::GetMouseY()));

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
