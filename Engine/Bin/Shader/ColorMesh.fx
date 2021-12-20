
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
	// 변수 뒤에 : 레지스터이름 + 번호 로 지정한다.
	// 번호를 안붙이면 0으로 지정된다.
	float3	Pos : POSITION;	// Vector3타입.
};

struct VertexPosOutput
{
	// SV가 붙으면 System Value이다. 이 값은 레지스터에 저장만 하고
	// 가져다 사용하면 안된다.
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
