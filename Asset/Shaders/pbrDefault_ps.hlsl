cbuffer MatrixBuffer
{
    matrix worldMatrix;
    matrix viewMatrix;
    matrix projectionMatrix;
    float4 debugColor;
};

Texture2D tBaseMap;
SamplerState tBaseSmp;

struct PSIn
{
    float4 position : SV_POSITION;
    float3 normal : NORMAL;
    float2 uv : TEXCOORD;
};

float4 MainPS(PSIn psi) : SV_TARGET
{
    float3 lightDir = normalize(float3(1, 1, -1));
    float lightPow = 0.8;

    float light = max(dot(lightDir, psi.normal), 0.0) * lightPow;

    float4 color;

    color = float4(debugColor.xyz * light, 1.0);
    
    return color;
}