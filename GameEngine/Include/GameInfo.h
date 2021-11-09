
#pragma once

#include <Windows.h>
#include <list>
#include <vector>
#include <unordered_map>

#define SAFE_DELETE(p)	if (p) { delete p; p = nullptr; }

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