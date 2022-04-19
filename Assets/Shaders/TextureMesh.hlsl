
#define UINT_MAX 1 << 16

struct VS_INPUT{
    float3 position : POSITION;
    float3 normal : NORMAL;
    float2 texcoord : TEXCOORD0;
    float4 color : COLOR;
};

cbuffer uniforms : register(b1)
{
    float4x4 u_ViewProjection;
    float4x4 u_Transform;
    float2 u_Resolution;
    float u_Time;
    float u_TimeDelta;
    float2 u_Mouse;
}

struct VS_OUTPUT {
    float4 position : SV_POSITION;
    float4 color : COLOR;
};

// Vertex shader which passes position and color through to rasterizer.
VS_OUTPUT VSMain(const uint vertexId : SV_VERTEXID, VS_INPUT v)
{
    VS_OUTPUT output;
    output.position = mul(float4(v.position, 1.0), u_Transform);
    output.position = mul(output.position, u_ViewProjection);
    // output.position.x *= abs(sin(u_Time));
    output.color = float4(abs(sin(u_Mouse.x / u_Resolution.x)), 0.0, 1.0, 1.0);
    return output;
}

// Fragment shader that just outputs color passed from rasterizer.
float4 PSMain(VS_OUTPUT input) : SV_TARGET
{
    return input.color;
}