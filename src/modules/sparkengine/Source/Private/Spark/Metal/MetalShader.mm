#include <string>
#ifdef SPARKENGINE_ENABLE_RENDERER_METAL

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

#include "ShaderConductor/ShaderConductor.hpp"

#include "simd/simd.h"

#include "Spark/Engine/Mesh/MeshComponent.h"


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
    [context->m_CommandEncoder setVertexBuffer:buffer offset:0 atIndex:0];
    [context->m_CommandEncoder setFragmentBuffer:buffer offset:0 atIndex:0];
}

void MetalShader::Unbind() const
{
    
}

void MetalShader::UploadUniformFloat(const std::string &name, const float& f)
{
    const char* p = (char*)&f;
    m_UniformsData.push_back({sizeof(float), p});
}

void MetalShader::UploadUniformFloat2(const std::string &name, const glm::vec2 &vector)
{
    const char* p = (char*)glm::value_ptr(vector);
    m_UniformsData.push_back({sizeof(simd::float2), p});
}

void MetalShader::UploadUniformFloat3(const std::string &name, const glm::vec3 &vector)
{
    const char* p = (char*)glm::value_ptr(vector);
    m_UniformsData.push_back({sizeof(simd::float3), p});
}

void MetalShader::UploadUniformFloat4(const std::string &name, const glm::vec4 &vector)
{
    const char* p = (char*)glm::value_ptr(vector);
    m_UniformsData.push_back({sizeof(simd::float4), p});
}

void MetalShader::UploadUniformInt(const std::string &name, int i)
{
    const char* p = (char*)&i;
    m_UniformsData.push_back({sizeof(int), p});
}

void MetalShader::UploadUniformMat3(const std::string &name, const glm::mat3 &matrix)
{
    const char* p = (char*)glm::value_ptr(matrix);
    m_UniformsData.push_back({sizeof(simd::float3x3), p});
}

void MetalShader::UploadUniformMat4(const std::string &name, const glm::mat4 &matrix)
{
    const char* p = (char*)glm::value_ptr(matrix);
    m_UniformsData.push_back({sizeof(simd::float4x4), p});
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
    // Prepare the shader compiler parameters
    ShaderConductor::Compiler::SourceDesc sourceDesc;
    sourceDesc.source = sourceShader.c_str();

    ShaderConductor::Compiler::Options options;
    options.shaderModel.major_ver = 6;
    options.shaderModel.minor_ver = 0;
    // options.enableDebugInfo = true;

    ShaderConductor::Compiler::TargetDesc targetDesc;
    targetDesc.language = ShaderConductor::ShadingLanguage::Msl_macOS;

    ShaderConductor::Compiler compiler;


    // Compile Vertex Shader
    sourceDesc.stage = ShaderConductor::ShaderStage::VertexShader;
    sourceDesc.entryPoint = "VSMain";
    ShaderConductor::Compiler::ResultDesc result = compiler.Compile(sourceDesc, options, targetDesc);
    if(result.hasError)
    {
        ShaderConductor::Blob errorMsgBlob = result.errorWarningMsg;
        std::string errorMsgStr = std::string(reinterpret_cast<const char*>(errorMsgBlob.Data()), errorMsgBlob.Size());
        
        CORE_LOGF("Vertex Shader stage \"{0}\" compilation failure!", m_Name);
        CORE_LOGF("{0}", errorMsgStr);
        CORE_ASSERT(false, "Vertex Shader stage compilation failure!");
    }
    std::string compiledVertexShaderSource = std::string(reinterpret_cast<const char*>(result.target.Data()), result.target.Size());
    NSString* VSSource = [NSString stringWithCString:compiledVertexShaderSource.c_str() encoding:[NSString defaultCStringEncoding]];

    // Compile Pixel Shader
    sourceDesc.stage = ShaderConductor::ShaderStage::PixelShader;
    sourceDesc.entryPoint = "PSMain";
    result = compiler.Compile(sourceDesc, options, targetDesc);
    if(result.hasError)
    {
        ShaderConductor::Blob errorMsgBlob = result.errorWarningMsg;
        std::string errorMsgStr = std::string(reinterpret_cast<const char*>(errorMsgBlob.Data()), errorMsgBlob.Size());
        
        CORE_LOGF("Pixel Shader stage \"{0}\" compilation failure!", m_Name);
        CORE_LOGF("{0}", errorMsgStr);
        CORE_ASSERT(false, "Pixel Shader stage compilation failure!");
    }
    std::string compiledPixelShaderSource = std::string(reinterpret_cast<const char*>(result.target.Data()), result.target.Size());
    NSString* PSSource = [NSString stringWithCString:compiledPixelShaderSource.c_str() encoding:[NSString defaultCStringEncoding]];

    
    Ref<MetalGraphicsContext> context = std::static_pointer_cast<MetalGraphicsContext>(Renderer::GetGraphicsContext());
    
    // Write generated shader source to file for debugging
    // TODO - Enable this when debugging is needed
    {
        // Concat Shader Sources
        std::string finalShaderSource = compiledVertexShaderSource + "\n" + compiledPixelShaderSource;
        NSString* source = [NSString stringWithCString:finalShaderSource.c_str() encoding:[NSString defaultCStringEncoding]];

        IPlatformFile *platformFile = IPlatformFile::Get();
        char* filename = (char*)malloc(strlen(m_Name.c_str()) + 13);
        strcpy(filename, m_Name.c_str());
        strcat(filename, ".debug.metal");
        IFileHandle* file = platformFile->OpenWrite(filename);
        file->Write(reinterpret_cast<const uint8*>(finalShaderSource.c_str()), finalShaderSource.size());
        file->Flush();
        delete file;
    }

    NSError* errors = nil;
    id<MTLLibrary> VSLibrary = [context->m_Device newLibraryWithSource:VSSource options:nil error:&errors];
    id<MTLLibrary> PSLibrary = [context->m_Device newLibraryWithSource:PSSource options:nil error:&errors];
    if(errors)
    {
        CORE_LOGF("Shader \"{0}\" compilation failure!", m_Name);
        CORE_LOGF("{0}", std::string([errors.localizedDescription UTF8String]));
        CORE_ASSERT(false, "Shader compilation failure!");
    }

    // Prepare Pipeline Descriptor -------
    m_PipelineDescriptor = [[MTLRenderPipelineDescriptor alloc] init];
    m_PipelineDescriptor.vertexFunction = [VSLibrary newFunctionWithName:@"VSMain"];
    m_PipelineDescriptor.fragmentFunction = [PSLibrary newFunctionWithName:@"PSMain"];
    m_PipelineDescriptor.colorAttachments[0].pixelFormat = MTLPixelFormatBGRA8Unorm;
    
    m_PipelineDescriptor.vertexDescriptor = [[MTLVertexDescriptor alloc] init];
    // Position
    m_PipelineDescriptor.vertexDescriptor.attributes[0].format = MTLVertexFormatFloat3;
    m_PipelineDescriptor.vertexDescriptor.attributes[0].offset = (int)offsetof(VertexData, Position);
    m_PipelineDescriptor.vertexDescriptor.attributes[0].bufferIndex = 1;
    // Normal
    m_PipelineDescriptor.vertexDescriptor.attributes[1].format = MTLVertexFormatFloat3;
    m_PipelineDescriptor.vertexDescriptor.attributes[1].offset = (int)offsetof(VertexData, Normal);
    m_PipelineDescriptor.vertexDescriptor.attributes[1].bufferIndex = 1;
    // UV
    m_PipelineDescriptor.vertexDescriptor.attributes[2].format = MTLVertexFormatFloat2;
    m_PipelineDescriptor.vertexDescriptor.attributes[2].offset = (int)offsetof(VertexData, UV);
    m_PipelineDescriptor.vertexDescriptor.attributes[2].bufferIndex = 1;
    // Color
    m_PipelineDescriptor.vertexDescriptor.attributes[3].format = MTLVertexFormatFloat4;
    m_PipelineDescriptor.vertexDescriptor.attributes[3].offset = (int)offsetof(VertexData, Color);
    m_PipelineDescriptor.vertexDescriptor.attributes[3].bufferIndex = 1;

    m_PipelineDescriptor.vertexDescriptor.layouts[1].stride = sizeof(VertexData);
    
    m_RenderPipelineState = [context->m_Device newRenderPipelineStateWithDescriptor:m_PipelineDescriptor error:nil];
}


} // namespace Spark

#endif //SPARKENGINE_ENABLE_RENDERER_METAL