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

    void OpenGLPlatformRendererAPI::Init()
    {
        s_API = API::OpenGL; // Set current render as OpenGL;
        
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        
        glEnable(GL_DEPTH_TEST);
    }

    void OpenGLPlatformRendererAPI::SetClearColor(const glm::vec4 color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
    }

    void OpenGLPlatformRendererAPI::Clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void OpenGLPlatformRendererAPI::DrawIndexed(const Ref<IVertexArray> &vertexArray)
    {
        glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
    }

    void OpenGLPlatformRendererAPI::SetViewport(uint32 X, uint32 Y, uint32 Width, uint32 Height)
    {
        glViewport(X, Y, Width, Height);
    }

} // namespace Spark
