#include "Basic.hlsli"

float4 PS(VertexPosHWNormalTex pIn) : SV_Target
{
	float4 yaya = g_Tex.Sample(g_SamLinear, pIn.Tex);
	float4 yaya1 = yaya_Tex.Sample(g_SamLinear, pIn.Tex);

	return yaya * yaya1;
}