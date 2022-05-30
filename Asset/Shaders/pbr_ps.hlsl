cbuffer MatrixBuffer
{
    matrix worldMatrix;
    matrix viewMatrix;
    matrix projectionMatrix;
};

struct PSIn
{
    float4 position : SV_POSITION;
    float4 color : Color;
};

float4 MainPS(PSIn psi) : SV_TARGET
{
    return float4(frac(psi.color.x), frac(psi.color.y), frac(psi.color.z), 1.0);
    // return float4(psi.color.xyz, 1.0f);
}