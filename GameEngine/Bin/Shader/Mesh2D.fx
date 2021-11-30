
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

VertexUVOutput Mesh2DVS(VertexUV input)
{
	VertexUVOutput	output = (VertexUVOutput)0;

	float3	Pos = input.Pos - g_Pivot * g_MeshSize;

	output.Pos = mul(float4(Pos, 1.f), g_matWVP);
	output.UV = input.UV;

	return output;
}

PSOutput_Single Mesh2DPS(VertexUVOutput input)
{
	PSOutput_Single	output = (PSOutput_Single)0;

	output.Color = g_BaseTexture.Sample(g_LinearSmp, input.UV);

	return output;
}
