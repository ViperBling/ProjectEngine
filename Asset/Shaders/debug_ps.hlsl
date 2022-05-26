struct PSIn
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
};

float4 MainPS(PSIn psi) : SV_TARGET
{
    return psi.color;
}