
struct PSOutput_Single
{
	float4	Color : SV_TARGET;
};

cbuffer Transform : register(b0)
{
	matrix	g_matWorld;
	matrix	g_matView;
	matrix	g_matProj;
	matrix	g_matWV;
	matrix	g_matWVP;
	matrix	g_matVP;
	float3	g_Pivot;
	float	g_TransformEmpty1;
	float3	g_MeshSize;
	float	g_TransformEmpty;
};



SamplerState	g_PointSmp : register(s0);
SamplerState	g_LinearSmp : register(s1);
SamplerState	g_AnisotropicSmp : register(s2);

Texture2D		g_BaseTexture	: register(t0);
