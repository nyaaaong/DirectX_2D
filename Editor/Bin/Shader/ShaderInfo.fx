
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

cbuffer Material : register(b1)
{
	float4	g_MtrlBaseColor;
	float	g_MtrlOpacity;
	float3	g_MtrlEmpty;
};

cbuffer Standard2D : register(b2)
{
	int		g_Animation2DEnable;
	float3	g_Standard2DEmpty;
};

cbuffer	GlobalCBuffer : register(b3)
{
	float	g_DeltaTime;
	float	g_AccTime;
	float2	g_Resolution;
	float2	g_NoiseResolution;
	float2	g_GlobalEmpty;
};

SamplerState	g_PointSmp : register(s0);
SamplerState	g_LinearSmp : register(s1);
SamplerState	g_AnisotropicSmp : register(s2);

SamplerState	g_BaseSmp : register(s3);

Texture2D		g_BaseTexture	: register(t0);

Texture2D		g_NoiseTexture	: register(t100);

static float Gaussian5x5[25] =
{
	0.003765f, 0.015019f, 0.023792f, 0.015019f, 0.003765f,
	0.015019f, 0.059912f, 0.094907f, 0.059912f, 0.015019f,
	0.023792f, 0.094907f, 0.150342f, 0.094907f, 0.023792f,
	0.015019f, 0.059912f, 0.094907f, 0.059912f, 0.015019f,
	0.003765f, 0.015019f, 0.023792f, 0.015019f, 0.003765f
};

float GaussianSample(int2 UV, Texture2D Tex)
{
	float4	Output = (float4)0.f;

	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			int2	ConvertUV = UV + int2(i - 2, j - 2);

			if (ConvertUV.x < 0)
				ConvertUV.x = 0;

			else if (ConvertUV.x > g_NoiseResolution.x)
				ConvertUV.x = g_NoiseResolution.x - 1;

			if (ConvertUV.y < 0)
				ConvertUV.y = 0;

			else if (ConvertUV.y > g_NoiseResolution.y)
				ConvertUV.y = g_NoiseResolution.y - 1;

			Output += Tex[ConvertUV] * Gaussian5x5[i * 5 + j];
		}
	}

	return Output.x;
}

float Rand(float Key)
{
	float2	UV = float2(Key + g_AccTime, g_AccTime);

	UV.y += sin(UV.x * 2.f * 3.141592f);

	if (UV.x > 0.f)
		UV.x = frac(UV.x);

	else
		UV.x = 1.f - abs(UV.x);

	if (UV.y > 0.f)
		UV.y = frac(UV.y);

	else
		UV.y = 1.f - abs(UV.y);

	UV = UV * g_NoiseResolution;

	return GaussianSample(UV, g_NoiseTexture);
}
