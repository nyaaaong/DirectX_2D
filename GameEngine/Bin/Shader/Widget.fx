
#include "ShaderInfo.fx"


struct VertexUV
{
	// ���� �ڿ� : ���������̸� + ��ȣ �� �����Ѵ�.
	// ��ȣ�� �Ⱥ��̸� 0���� �����ȴ�.
	float3	Pos : POSITION;	// Vector3Ÿ��.
	float2	UV	: TEXCOORD;
};

struct VertexUVOutput
{
	// SV�� ������ System Value�̴�. �� ���� �������Ϳ� ���常 �ϰ�
	// ������ ����ϸ� �ȵȴ�.
	float4	Pos : SV_POSITION;
	float2	UV	: TEXCOORD;
};

cbuffer WidgetCBuffer : register(b11)
{
	float4	g_WidgetTint;
	matrix	g_matWidgetWP;
	int		g_WidgetUseTexture;
	float3	g_WidgetEmpty;
};

cbuffer ProgressBarCBuffer : register(b12)
{
	float	g_ProgressBarPercent;
	int		g_ProgressBarDir;
	float2	g_ProgressBarEmpty;
};

VertexUVOutput WidgetVS(VertexUV input)
{
	VertexUVOutput	output = (VertexUVOutput)0;

	output.Pos = mul(float4(input.Pos, 1.f), g_matWidgetWP);
	output.UV = input.UV;

	return output;
}

#define	PROGRESSBAR_RIGHTTOLEFT	0
#define	PROGRESSBAR_LEFTTORIGHT	1
#define	PROGRESSBAR_TOPTOBOTTOM	2
#define	PROGRESSBAR_BOTTOMTOTOP	3

VertexUVOutput ProgressBarVS(VertexUV input)
{
	VertexUVOutput	output = (VertexUVOutput)0;

	float3	Pos = input.Pos;
	float2	UV = input.UV;

	// ������ -> ����
	if (g_ProgressBarDir == PROGRESSBAR_RIGHTTOLEFT)
	{
		if (Pos.x == 1.f)
			Pos.x = g_ProgressBarPercent;

		if (UV.x == 1.f)
			UV.x = g_ProgressBarPercent;
	}

	// ���� -> ������
	if (g_ProgressBarDir == PROGRESSBAR_LEFTTORIGHT)
	{
		if (Pos.x == 0.f)
			Pos.x = 1.f - g_ProgressBarPercent;

		if (UV.x == 0.f)
			UV.x = 1.f - g_ProgressBarPercent;
	}

	// �� -> �Ʒ�
	if (g_ProgressBarDir == PROGRESSBAR_TOPTOBOTTOM)
	{
		if (Pos.y == 1.f)
			Pos.y = 1.f - g_ProgressBarPercent;

		if (UV.y == 0.f)
			UV.y = g_ProgressBarPercent;
	}

	// �Ʒ� -> ��
	if (g_ProgressBarDir == PROGRESSBAR_BOTTOMTOTOP)
	{
		if (Pos.y == 0.f)
			Pos.y = g_ProgressBarPercent;

		if (UV.y == 1.f)
			UV.y = 1.f - g_ProgressBarPercent;
	}

	output.Pos = mul(float4(Pos, 1.f), g_matWidgetWP);
	output.UV = UV;

	return output;
}

PSOutput_Single WidgetPS(VertexUVOutput input)
{
	PSOutput_Single	output = (PSOutput_Single)0;

	if (g_WidgetUseTexture == 1)
	{
		float4	BaseTextureColor = g_BaseTexture.Sample(g_BaseSmp, input.UV);

		output.Color.rgb = BaseTextureColor.rgb * g_WidgetTint.rgb;

		if (BaseTextureColor.a == 0.f)
			clip(-1);

		output.Color.a = BaseTextureColor.a * g_WidgetTint.a;
	}

	else
	{
		output.Color = g_WidgetTint;
	}

	return output;
}
