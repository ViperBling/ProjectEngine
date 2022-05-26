struct VSIn
{
    float3 position : POSITION;
    float4 color : COLOR;
};

struct VSOut
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
};

VSOut MainVS(VSIn vsi)
{
    VSOut vso;

    vso.position = float4(vsi.position, 1.0f);
    vso.color = vsi.color;

    return vso;
}