#pragma once

#include "Spark/Core/CoreTypes.h"
#include "Spark/Renderer/IVertexArray.h"
#include "Spark/Renderer/IShader.h"
#include "Spark/Renderer/OrthographicCamera.h"
#include "Spark/Renderer/Texture.h"

#include "sparkengine.api.gen.h"

namespace Spark
{

    class SPARKENGINE_API Renderer2D
    {
    private:
        struct Renderer2DData
        {
            glm::mat4 ViewProjectionMatrix;
            Ref<IVertexArray> QuadVertexArray;
            Ref<IShader> TextureShader;
            Ref<Texture> WhiteTexture;
        };
        static Renderer2DData *s_Data;

    public:
        static void Init();
        static void Shutdown();

        static void BeginScene(OrthographicCamera &camera);
        static void EndScene();

        static void DrawQuad(const glm::vec2 &Position, const glm::vec2 &Size, const glm::vec4 &Color);
        static void DrawQuad(const glm::vec3 &Position, const glm::vec2 &Size, const glm::vec4 &Color);
        
        static void DrawQuad(const glm::vec2 &Position, const glm::vec2 &Size, const glm::vec4 &Color, const Ref<Texture>& Texture);
        static void DrawQuad(const glm::vec3 &Position, const glm::vec2 &Size, const glm::vec4 &Color, const Ref<Texture>& Texture);
    };

} // namespace Spark