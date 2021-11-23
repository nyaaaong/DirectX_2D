
#include "ShaderInfo.fx"

struct VertexColor
{
	// 변수 뒤에 : 레지스터이름 + 번호 로 지정한다.
	// 번호를 안붙이면 0으로 지정된다.
	float3	Pos : POSITION;	// Vector3타입.
	float4	Color : COLOR;
};

struct VertexColorOutput
{
	// SV가 붙으면 System Value이다. 이 값은 레지스터에 저장만 하고
	// 가져다 사용하면 안된다.
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
