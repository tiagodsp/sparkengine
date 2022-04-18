#define UINT_MAX 1 << 16

float3 position : POSITION0;

cbuffer uniforms : register(b1)
{
    float4x4 viewProjection;
    float4x4 transform;
    float4 color;
}

float4 PSMain() : SV_Target0
{
    return float4(1, 0, 0, 1);
}

float4 VSMain(uint vertexID : SV_VERTEXID) : SV_Position
{
    return viewProjection * transform * float4x1(position, 1.0);
}