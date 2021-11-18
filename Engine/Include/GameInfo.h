
#pragma once

#include <Windows.h>
#include <list>
#include <vector>
#include <unordered_map>
#include <crtdbg.h>
#include <functional>
#include <string>
#include <math.h>
#include <algorithm>
#include <d3d11.h>
#include <d3dcompiler.h>

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix.h"
#include "SharedPtr.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "d3dcompiler.lib")

#define ASSERT(msg)	assert(!TEXT(msg))

#define	ROOT_PATH	"Root"
#define SHADER_PATH	"Shader"

#define SAFE_DELETE(p)	if (p) { delete p; p = nullptr; }
#define SAFE_RELEASE(p)	if (p) { p->Release(); p = nullptr; }

#define DECLARE_SINGLE(Type)\
private:\
	static Type* m_pInst;\
public:\
	static Type* GetInst()\
	{\
		if (!m_pInst)\
			m_pInst = new Type;\
		return m_pInst;\
	}\
	static void DestroyInst()\
	{\
		SAFE_DELETE(m_pInst);\
	}\
private:\
	Type();\
	~Type();

#define DEFINITION_SINGLE(Type)	Type*	Type::m_pInst = nullptr;

struct Resolution
{
	unsigned int	iWidth;
	unsigned int	iHeight;
};

struct VertexColor
{
	Vector3	tPos;
	Vector4	tColor;

	VertexColor()
	{
	}

	VertexColor(const Vector3& _tPos, const Vector4& _tColor)	:
		tPos(_tPos),
		tColor(_tColor)
	{
	}
};

struct VertexBuffer
{
	ID3D11Buffer* pBuffer;
	int		iSize;
	int		iCount;

	VertexBuffer() :
		pBuffer(nullptr),
		iSize(0),
		iCount(0)
	{
	}

	~VertexBuffer()
	{
		SAFE_RELEASE(pBuffer);
	}
};

struct IndexBuffer
{
	ID3D11Buffer* pBuffer;
	int		iSize;
	int		iCount;
	DXGI_FORMAT	eFmt;

	IndexBuffer() :
		pBuffer(nullptr),
		iSize(0),
		iCount(0),
		eFmt(DXGI_FORMAT_UNKNOWN)
	{
	}

	~IndexBuffer()
	{
		SAFE_RELEASE(pBuffer);
	}
};

struct MeshContainer
{
	VertexBuffer	tVB;
	std::vector<IndexBuffer>	vecIB;
	D3D11_PRIMITIVE_TOPOLOGY	ePrimitive;
};