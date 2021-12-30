
#include "ShaderInfo.fx"

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

cbuffer Collider : register(b11)
{
	float4	g_ColliderColor;
	matrix	g_matColliderWVP;
};

VertexPosOutput ColliderMeshVS(VertexPos input)
{
	VertexPosOutput	output = (VertexPosOutput)0;

	output.Pos = mul(float4(input.Pos, 1.f), g_matColliderWVP);

	return output;
}

PSOutput_Single ColliderMeshPS(VertexPosOutput input)
{
	PSOutput_Single	output = (PSOutput_Single)0;

	output.Color.rgb = g_ColliderColor.rgb;
	output.Color.a = g_ColliderColor.a;

	return output;
}
