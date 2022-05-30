cbuffer MatrixBuffer
{
    matrix worldMatrix;
    matrix viewMatrix;
    matrix projectionMatrix;
    float4 debugColor;
};

struct PSIn
{
    float4 position : SV_POSITION;
    float4 color : Color;
};

float4 MainPS(PSIn psi) : SV_TARGET
{
    return debugColor;
}