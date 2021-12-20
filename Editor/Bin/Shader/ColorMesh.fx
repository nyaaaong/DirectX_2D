
#include "ShaderInfo.fx"

struct VertexColor
{
	// ���� �ڿ� : ���������̸� + ��ȣ �� �����Ѵ�.
	// ��ȣ�� �Ⱥ��̸� 0���� �����ȴ�.
	float3	Pos : POSITION;	// Vector3Ÿ��.
	float4	Color : COLOR;
};

struct VertexColorOutput
{
	// SV�� ������ System Value�̴�. �� ���� �������Ϳ� ���常 �ϰ�
	// ������ ����ϸ� �ȵȴ�.
	float4	Pos : SV_POSITION;
	float4	Color : COLOR;
};

VertexColorOutput ColorMeshVS(VertexColor input)
{
	VertexColorOutput	output = (VertexColorOutput)0;

	float3	Pos = input.Pos - g_Pivot * g_MeshSize;

	output.Pos = mul(float4(Pos, 1.f), g_matWVP);
	output.Color = input.Color;

	return output;
}

struct VertexColorPSOutput
{
	float4	Color : SV_TARGET;
};

VertexColorPSOutput ColorMeshPS(VertexColorOutput input)
{
	VertexColorPSOutput	output = (VertexColorPSOutput)0;

	output.Color = input.Color;

	return output;
}

struct VertexPos
{
	// ���� �ڿ� : ���������̸� + ��ȣ �� �����Ѵ�.
	// ��ȣ�� �Ⱥ��̸� 0���� �����ȴ�.
	float3	Pos : POSITION;	// Vector3Ÿ��.
};

struct VertexPosOutput
{
	// SV�� ������ System Value�̴�. �� ���� �������Ϳ� ���常 �ϰ�
	// ������ ����ϸ� �ȵȴ�.
	float4	Pos : SV_POSITION;
};

VertexPosOutput PosMeshVS(VertexPos input)
{
	VertexPosOutput	output = (VertexPosOutput)0;

	float3	Pos = input.Pos - g_Pivot * g_MeshSize;

	output.Pos = mul(float4(Pos, 1.f), g_matWVP);

	return output;
}

PSOutput_Single PosMeshPS(VertexPosOutput input)
{
	PSOutput_Single	output = (PSOutput_Single)0;

	output.Color.rgb = g_MtrlBaseColor.rgb;
	output.Color.a = g_MtrlOpacity;

	return output;
}
