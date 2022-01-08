
#include "ShaderInfo.fx"


struct VertexUV
{
	// 변수 뒤에 : 레지스터이름 + 번호 로 지정한다.
	// 번호를 안붙이면 0으로 지정된다.
	float3	Pos : POSITION;	// Vector3타입.
	float2	UV	: TEXCOORD;
};

struct VertexUVOutput
{
	// SV가 붙으면 System Value이다. 이 값은 레지스터에 저장만 하고
	// 가져다 사용하면 안된다.
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

VertexUVOutput WidgetVS(VertexUV input)
{
	VertexUVOutput	output = (VertexUVOutput)0;

	output.Pos = mul(float4(input.Pos, 1.f), g_matWidgetWP);
	output.UV = input.UV;

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
