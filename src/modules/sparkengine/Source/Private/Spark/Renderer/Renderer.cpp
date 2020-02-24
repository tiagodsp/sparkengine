#pragma once
#include "sparkengine.PCH.h"
#include "Spark/Renderer/RenderCommand.h"
#include "Spark/Renderer/Renderer.h"

namespace Spark
{

void Renderer::BeginScene()
{

}
void Renderer::EndScene()
{

}

void Renderer::Submit(const std::shared_ptr<IVertexArray>& vertexArray)
{
    vertexArray->Bind();
    RenderCommand::DrawIndexed(vertexArray);
}

} // namespace Spark