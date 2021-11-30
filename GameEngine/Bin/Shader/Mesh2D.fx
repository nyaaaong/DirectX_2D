
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
