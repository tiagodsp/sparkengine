#include "sparkengine.PCH.h"
#include "OpenGLPlatformRendererAPI.h"

#include "glad/glad.h"

namespace Spark
{

OpenGLPlatformRendererAPI::OpenGLPlatformRendererAPI(/* args */)
{
}

OpenGLPlatformRendererAPI::~OpenGLPlatformRendererAPI()
{
}

void OpenGLPlatformRendererAPI::SetClearColor(const glm::vec4 color)
{
    glClearColor(color.r, color.g, color.b, color.a);
}

void OpenGLPlatformRendererAPI::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLPlatformRendererAPI::DrawIndexed(const std::shared_ptr<IVertexArray> &vertexArray)
{
    glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
}

} // namespace Spark
