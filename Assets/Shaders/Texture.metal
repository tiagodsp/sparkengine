#include <metal_stdlib>

using namespace metal;

typedef struct
{
    float4x4 viewProjection;
    float4x4 transform;
    float4 color;
    // int textureIndex;
} Uniforms;

struct Vertex
{
    packed_float3 position;
    // float3 normal;
    // float2 texcoord;
    // float3 color;
};

struct RasterizerData
{
    float4 position [[position]];
    float4 color;
};

// Vertex shader which passes position and color through to rasterizer.
vertex RasterizerData vertexFunction(uint vertexID [[ vertex_id ]],
                                        constant Vertex *v [[ buffer(0) ]],
                                        constant Uniforms *u [[ buffer(1) ]])
{
    RasterizerData out;
    out.position = u->viewProjection * u->transform * vector_float4(v[vertexID].position.xyz, 1.0);
    out.color = u->color;
    return out;
}

// Fragment shader that just outputs color passed from rasterizer.
fragment float4 fragmentFunction(RasterizerData in [[stage_in]])
{
    return in.color;
}