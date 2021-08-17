#include <metal_stdlib>

using namespace metal;

struct Uniforms
{
    float4x4 viewProjection;
    float4x4 transform;
};

struct Vertex
{
    packed_float3 position;
    packed_float3 normal;
    packed_float2 texcoord;
    packed_float4 color;
};

struct RasterizerData
{
    float4 position [[position]];
    float4 color;
};

// Vertex shader which passes position and color through to rasterizer.
vertex RasterizerData vertexFunction(const uint vertexID [[ vertex_id ]],
                                        constant Vertex *v [[ buffer(0) ]],
                                        constant Uniforms* u [[ buffer(1) ]])
{
    RasterizerData out;
    out.position = u->viewProjection * u->transform * vector_float4(v[vertexID].position.xyz, 1.0);
    out.color = float4(0,0,1,1);
    return out;
}

// Fragment shader that just outputs color passed from rasterizer.
fragment float4 fragmentFunction(RasterizerData in [[stage_in]])
{
    return in.color;
}