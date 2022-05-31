cbuffer MatrixBuffer
{
    matrix worldMatrix;
    matrix viewMatrix;
    matrix projectionMatrix;
    float4 debugColor;
};

struct VSIn
{
    float3 position : POSITION;
    float3 normal : NORMAL;
    float2 uv : TEXCOORD;
};

struct VSOut
{
    float4 position : SV_POSITION;
    float3 normal : NORMAL;
    float2 uv : TEXCOORD;
};

VSOut MainVS(VSIn vsi)
{
    VSOut vso;

    vso.position = mul(float4(vsi.position, 1.0), worldMatrix);
    vso.position = mul(vso.position, viewMatrix);
    vso.position = mul(vso.position, projectionMatrix);

    float4 worldNormal = mul(float4(vsi.normal, 0.0), worldMatrix);
    vso.normal = worldNormal.xyz;
    vso.uv = vsi.uv;
    
    return vso;
}