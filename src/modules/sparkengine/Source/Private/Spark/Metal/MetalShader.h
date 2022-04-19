#pragma once
#include "Spark/Renderer/IShader.h"
#include <Metal/Metal.h>
#include "glad/glad.h"

namespace Spark
{

struct UniformData {
    size_t size;
    const char* data;
};


/**
 * Metal Shader implementation
 */
class MetalShader final : public IShader
{
public:
    MetalShader(const std::string &filepath);
    MetalShader(const std::string &name, const std::string &sourceShader);
    
    ~MetalShader();

    virtual void Bind() override;
    virtual void Unbind() const override;

    virtual const std::string &GetName() const override { return m_Name; };

    // Float Uniforms -----------------
    virtual void UploadUniformFloat(const std::string &name, const float& f) override;
    virtual void UploadUniformFloat2(const std::string &name, const glm::vec2 &vector) override;
    virtual void UploadUniformFloat3(const std::string &name, const glm::vec3 &vector) override;
    virtual void UploadUniformFloat4(const std::string &name, const glm::vec4 &vector) override;

    // Interger uniforms -----------------
    virtual void UploadUniformInt(const std::string &name, int i) override;

    // Matrix uniforms -----------------
    virtual void UploadUniformMat3(const std::string &name, const glm::mat3 &matrix) override;
    virtual void UploadUniformMat4(const std::string &name, const glm::mat4 &matrix) override;

private:
    std::string ReadFile(const std::string& filepath);
    std::unordered_map<GLenum, std::string> PreProcess(const std::string& filepath);
    void Compile(std::string sourceShader);

private:
    std::string m_Name;
    MTLRenderPipelineDescriptor* m_PipelineDescriptor;
    id<MTLRenderPipelineState> m_RenderPipelineState;
    id<MTLBuffer> m_UniformsBuffer;
    std::vector<UniformData> m_UniformsData;
    
};
} // namespace Spark
