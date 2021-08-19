#include "sparkengine.PCH.h"
#include "MetalShader.h"

#include <fstream>
#include <regex>
#include "Spark/Core/GenericPlatform/GenericPlatformFile.h"
#include "Spark/Renderer/Renderer.h"
#include "Spark/Metal/MetalPlatformRendererAPI.h"
#include <Metal/Metal.h>
#include "glm/gtc/type_ptr.hpp"
#include "Spark/Core/Misc/Paths.h"


namespace Spark
{

MetalShader::MetalShader(const std::string &filepath)
{
    std::string shaderSource = ReadFile(filepath);
    m_Name = Paths::GetBaseFilename(filepath);
    Compile(shaderSource);
}

MetalShader::MetalShader(const std::string &name, const std::string &sourceShader)
    : m_Name(name)
{
    Compile(sourceShader);
}

MetalShader::~MetalShader()
{
    [m_PipelineDescriptor release];
}

void MetalShader::Bind()
{
    Ref<MetalGraphicsContext> context = std::static_pointer_cast<MetalGraphicsContext>(Renderer::GetGraphicsContext());
    
    uint32 uniformBufferSize = 0;
    for(auto u : m_UniformsData)
    {
        uniformBufferSize += u.size;
    }
    
    char* bufferData = (char*) malloc(uniformBufferSize);
    
    uint32 offset = 0;
    for(auto u : m_UniformsData)
    {
        memcpy(bufferData + offset, u.data, u.size);
        offset += u.size;
    }

    id<MTLBuffer> buffer = [context->m_Device newBufferWithBytes:bufferData length:uniformBufferSize options:MTLResourceOptionCPUCacheModeDefault];
    delete bufferData;
    m_UniformsData.clear();
    
    [context->m_CommandEncoder setRenderPipelineState:m_RenderPipelineState];
    [context->m_CommandEncoder setVertexBuffer:buffer offset:0 atIndex:1];
}

void MetalShader::Unbind() const
{
    
}

void MetalShader::UploadUniformFloat(const std::string &name, float f)
{
    const char* p = (char*)&f;
    m_UniformsData.push_back({sizeof(float), p});
}

void MetalShader::UploadUniformFloat2(const std::string &name, const glm::vec2 &vector)
{
    const char* p = (char*)glm::value_ptr(vector);
    m_UniformsData.push_back({sizeof(glm::vec2), p});
}

void MetalShader::UploadUniformFloat3(const std::string &name, const glm::vec3 &vector)
{
    const char* p = (char*)glm::value_ptr(vector);
    m_UniformsData.push_back({sizeof(glm::vec3), p});
}

void MetalShader::UploadUniformFloat4(const std::string &name, const glm::vec4 &vector)
{
    const char* p = (char*)glm::value_ptr(vector);
    m_UniformsData.push_back({sizeof(glm::vec4), p});
}

void MetalShader::UploadUniformInt(const std::string &name, int i)
{
    const char* p = (char*)&i;
    m_UniformsData.push_back({sizeof(int), p});
}

void MetalShader::UploadUniformMat3(const std::string &name, const glm::mat3 &matrix)
{
    const char* p = (char*)glm::value_ptr(matrix);
    m_UniformsData.push_back({sizeof(glm::mat3), p});
}

void MetalShader::UploadUniformMat4(const std::string &name, const glm::mat4 &matrix)
{
    const char* p = (char*)glm::value_ptr(matrix);
    m_UniformsData.push_back({sizeof(glm::mat4), p});
}


std::string MetalShader::ReadFile(const std::string& filepath)
{
    IFileHandle* file = IPlatformFile::Get()->OpenRead(filepath.c_str());
    std::string result;
    if(file)
    {
        int64 size = IPlatformFile::Get()->FileSize(filepath.c_str());
        result.resize(size);
        file->Read(reinterpret_cast<uint8*>(result.data()), size);
    }
    else
    {
        CORE_LOGE("Could not open file {0}", filepath);
    }
    delete file;
    return result;
}

void MetalShader::Compile(std::string sourceShader)
{
    NSString* source = [NSString stringWithCString:sourceShader.c_str() encoding:[NSString defaultCStringEncoding]];
    
    Ref<MetalGraphicsContext> context = std::static_pointer_cast<MetalGraphicsContext>(Renderer::GetGraphicsContext());
    
    NSError* errors = nil;
    id<MTLLibrary> library = [context->m_Device newLibraryWithSource:source options:nil error:&errors];
    if(errors)
    {
        CORE_LOGF("Shader \"{0}\" compilation failure!", m_Name);
        CORE_LOGF("{0}", std::string([errors.localizedDescription UTF8String]));
        CORE_ASSERT(false, "Shader compilation failure!");
    }
    
    // Prepare Pipeline Descriptor -------
    m_PipelineDescriptor = [[MTLRenderPipelineDescriptor alloc] init];
    m_PipelineDescriptor.vertexFunction = [library newFunctionWithName:@"vertexFunction"];
    m_PipelineDescriptor.fragmentFunction = [library newFunctionWithName:@"fragmentFunction"];
    m_PipelineDescriptor.colorAttachments[0].pixelFormat = MTLPixelFormatBGRA8Unorm;
    
    m_RenderPipelineState = [context->m_Device newRenderPipelineStateWithDescriptor:m_PipelineDescriptor error:nil];
}


} // namespace Spark
