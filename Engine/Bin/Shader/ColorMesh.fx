
#include "ShaderInfo.fx"

struct VertexColor
{
	float3	tPos : POSITION; // 0��
	float4	tColor : COLOR;
};

struct VertexColorOutput
{
	float4	tPos : SV_POSITION; // SV : System Value, �������Ϳ� ���常 �ϴ� ���. ���� ����ؼ� �ȵȴ�
	float4	tColor : COLOR;
};

VertexColorOutput ColorMeshVS(VertexColor tInput)
{
	VertexColorOutput	tOutput = (VertexColorOutput)0;

	tOutput.tPos = float4(tInput.tPos, 1.f);
	tOutput.tColor = tInput.tColor;

	return tOutput;
}

struct VertexColorPSOutput
{
	float4	tColor : SV_TARGET;
};

VertexColorPSOutput ColorMeshPS(VertexColorOutput tInput)
{
	VertexColorPSOutput	tOutput = (VertexColorPSOutput)0;

	tOutput.tColor = tInput.tColor;

	return tOutput;
}
