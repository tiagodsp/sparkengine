#include "sparkengine.PCH.h"
#include "Spark/Renderer/Renderer2D.h"
#include "Spark/Renderer/RenderCommand.h"
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtx/projection.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace Spark
{
    Renderer2D::Renderer2DData *Renderer2D::s_Data = new Renderer2D::Renderer2DData();

    void Renderer2D::Init()
    {

        float vertices[] =
            {
                -0.5f,-0.5f, 0.0f, 0.0f, 0.0f,
                 0.5f,-0.5f, 0.0f, 1.0f, 0.0f,
                 0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
                -0.5f, 0.5f, 0.0f, 0.0f, 1.0f
            };

        uint32 triangles[] = {0, 1, 2, 2, 3, 0};

        Ref<IVertexBuffer> quadVB = IVertexBuffer::Create(vertices, sizeof(vertices));
        quadVB->SetLayout({
            {Spark::ShaderDataType::Float3, "a_Position"},
            {Spark::ShaderDataType::Float2, "a_TexCoord"}
        });
        Ref<IIndexBuffer> quadIB = IIndexBuffer::Create(triangles, sizeof(triangles) / sizeof(uint32));

        s_Data->QuadVertexArray = IVertexArray::Create();
        s_Data->QuadVertexArray->AddVertexBuffer(quadVB);
        s_Data->QuadVertexArray->SetIndexBuffer(quadIB);

        s_Data->FlatColorShader = IShader::Create("Assets/Shaders/FlatColor.glsl");
        s_Data->TextureShader = IShader::Create("Assets/Shaders/Texture.glsl");
    }

    void Renderer2D::Shutdown()
    {
        delete s_Data;
    }

    void Renderer2D::BeginScene(OrthographicCamera &camera)
    {
        s_Data->ViewProjectionMatrix = camera.GetViewProjectionMatix();
        s_Data->FlatColorShader->Bind();
        s_Data->FlatColorShader->UploadUniformMat4("u_ViewProjection", s_Data->ViewProjectionMatrix);
        s_Data->FlatColorShader->Unbind();

        s_Data->TextureShader->Bind();
        s_Data->TextureShader->UploadUniformMat4("u_ViewProjection", s_Data->ViewProjectionMatrix);
        s_Data->TextureShader->Unbind();
    }
    void Renderer2D::EndScene()
    {
    }

    void Renderer2D::DrawQuad(const glm::vec2 &Position, const glm::vec2 &Size, const glm::vec4 &Color)
    {
        DrawQuad({Position.x, Position.y, 0.0f}, Size, Color);  
    }
    
    void Renderer2D::DrawQuad(const glm::vec3 &Position, const glm::vec2 &Size, const glm::vec4 &Color)
    {
        s_Data->FlatColorShader->Bind();
        s_Data->FlatColorShader->UploadUniformMat4("u_Transform", glm::mat4(1.0f) * glm::translate(Position) * glm::scale(glm::vec3({Size.x, Size.y, 1.0f})));
        s_Data->FlatColorShader->UploadUniformFloat4("u_Color", Color);

        s_Data->QuadVertexArray->Bind();
        RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
        s_Data->QuadVertexArray->Unbind();
        s_Data->FlatColorShader->Unbind();
    }

    void Renderer2D::DrawQuad(const glm::vec2 &Position, const glm::vec2 &Size, const glm::vec4 &Color, const Ref<Texture>& Texture)
    {
        DrawQuad({Position.x, Position.y, 0.0f}, Size, Color, Texture);  
    }
    
    void Renderer2D::DrawQuad(const glm::vec3 &Position, const glm::vec2 &Size, const glm::vec4 &Color, const Ref<Texture>& Texture)
    {
        s_Data->TextureShader->Bind();
        s_Data->TextureShader->UploadUniformMat4("u_Transform", glm::mat4(1.0f) * glm::translate(Position) * glm::scale(glm::vec3({Size.x, Size.y, 1.0f})));
        s_Data->TextureShader->UploadUniformFloat4("u_Color", Color);
        s_Data->TextureShader->UploadUniformInt("u_Texture", 0);

        Texture->Bind(0);
        s_Data->QuadVertexArray->Bind();
        RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
        s_Data->QuadVertexArray->Unbind();
        Texture->Unbind();
        s_Data->TextureShader->Unbind();
    }


} // namespace Spark
