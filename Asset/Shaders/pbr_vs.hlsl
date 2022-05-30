cbuffer MatrixBuffer
{
    matrix worldMatrix;
    matrix viewMatrix;
    matrix projectionMatrix;
};

struct VSIn
{
    float3 position : POSITION;
};

struct VSOut
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
};

VSOut MainVS(VSIn vsi)
{
    VSOut vso;
    float4 HPos = float4(vsi.position, 1.0);
    vso.position = mul(HPos, worldMatrix);
    vso.position = mul(vso.position, viewMatrix);
    vso.position = mul(vso.position, projectionMatrix);
    vso.color = float4(vsi.position, 1.0);
    
    return vso;
}