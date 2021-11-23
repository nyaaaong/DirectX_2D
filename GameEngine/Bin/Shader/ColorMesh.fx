
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

	output.Pos = float4(input.Pos, 1.f);
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
