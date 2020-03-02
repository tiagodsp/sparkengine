#pragma once
#include "sparkengine.PCH.h"
#include "Spark/Renderer/RenderCommand.h"
#include "Spark/Renderer/Renderer.h"

namespace Spark
{

Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData();

void Renderer::BeginScene(OrthographicCamera& camera)
{
    s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatix();
}
void Renderer::EndScene()
{

}

void Renderer::Submit(const std::shared_ptr<IShader>& shader, const std::shared_ptr<IVertexArray>& vertexArray, const glm::mat4& transform)
{
    shader->Bind();
    shader->UploadUniformMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
    shader->UploadUniformMat4("u_Transform", transform);

    vertexArray->Bind();
    RenderCommand::DrawIndexed(vertexArray);
    vertexArray->Unbind();
    
    shader->Unbind();
}

} // namespace Spark