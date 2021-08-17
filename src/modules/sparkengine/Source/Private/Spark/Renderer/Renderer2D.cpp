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

    struct VertexData{
        glm::vec3 position;
    };

    void Renderer2D::Init()
    {

        VertexData vertices[] =
//        {
//            {{-1.0f,-1.0f, 0.0f}},
//            {{ 0.0f, 1.0f, 0.0f}},
//            {{ 1.0f,-1.0f, 0.0f}}
//        };
            {
                {{-1.0f,-1.0f, 0.0f}},
                {{1.0f,-1.0f, 0.0f}},
                {{1.0f, 1.0f, 0.0f}},
                {{-1.0f, 1.0f, 0.0f}}
            };
            

        uint32 triangles[] = {0, 1, 2, 3, 2, 0};
//        uint32 triangles[] = {0, 1, 2};

        Ref<IVertexBuffer> quadVB = IVertexBuffer::Create((float*)vertices, sizeof(vertices));
        printf("SIZEOF: %lu\n",sizeof(VertexData));
        quadVB->SetLayout({
            {Spark::ShaderDataType::Float3, "a_Position"},
//            {Spark::ShaderDataType::Float3, "a_Color"},
//            {Spark::ShaderDataType::Float2, "a_TexCoord"}
        });
        Ref<IIndexBuffer> quadIB = IIndexBuffer::Create(triangles, sizeof(triangles) / sizeof(uint32));

        s_Data->QuadVertexArray = IVertexArray::Create();
        s_Data->QuadVertexArray->AddVertexBuffer(quadVB);
        s_Data->QuadVertexArray->SetIndexBuffer(quadIB);

        uint32 whitePixel = 0xFFFFFFFF;
        s_Data->WhiteTexture = Texture2D::Create(1, 1, Texture::TextureFormat::BGRA8);
        s_Data->WhiteTexture->SetTextureData(&whitePixel, sizeof(uint32), Texture::PixelFormat::RGBA);


        s_Data->TextureShader = IShader::Create("Assets/Shaders/Texture.metal");
    }

    void Renderer2D::Shutdown()
    {
        delete s_Data;
    }

    void Renderer2D::BeginScene(Camera &camera)
    {
        s_Data->ViewProjectionMatrix = camera.GetViewProjectionMatix();
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
        DrawQuad(Position, Size, Color, s_Data->WhiteTexture);
    }

    void Renderer2D::DrawQuad(const glm::vec2 &Position, const glm::vec2 &Size, const glm::vec4 &Color, const Ref<Texture>& Texture)
    {
        DrawQuad({Position.x, Position.y, 0.0f}, Size, Color, Texture);  
    }
    
    void Renderer2D::DrawQuad(const glm::vec3 &Position, const glm::vec2 &Size, const glm::vec4 &Color, const Ref<Texture>& Texture)
    {
        s_Data->TextureShader->UploadUniformMat4("u_ViewProjection", s_Data->ViewProjectionMatrix);
        s_Data->TextureShader->UploadUniformMat4("u_Transform", glm::mat4(1.0f) * glm::translate(Position + glm::vec3({0,0,-50})) * glm::scale(glm::vec3({Size.x, Size.y, 1.0f})));
        s_Data->TextureShader->UploadUniformFloat4("u_Color", Color);
        s_Data->TextureShader->UploadUniformFloat4("u_Color2", Color + glm::vec4(0,0,1,1));
//        s_Data->TextureShader->UploadUniformInt("u_Texture", 0);
        s_Data->TextureShader->Bind();

        //Texture->Bind(0);
        s_Data->QuadVertexArray->Bind();
        RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
        s_Data->QuadVertexArray->Unbind();
        //Texture->Unbind();
        s_Data->TextureShader->Unbind();
    }


} // namespace Spark
