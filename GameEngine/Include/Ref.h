#pragma once

#include "GameInfo.h"

class CRef
{
public:
	CRef();
	virtual ~CRef();

protected:
	std::string	m_strName;
	int		m_iRefCount;
	bool	m_bEnable;
	bool	m_bActive;

public:
	void Enable()
	{
		m_bEnable = true;
	}

	void Disable()
	{
		m_bEnable = false;
	}

	void Destroy()
	{
		m_bActive = true;
	}

	void AddRef()
	{
		++m_iRefCount;
	}

	int Release()
	{
		--m_iRefCount;

		if (m_iRefCount <= 0)
		{
			delete	this;
			return 0;
		}

		return m_iRefCount;
	}

	void SetName(const std::string& strName)
	{
		m_strName = strName;
	}

public:
	bool IsEnable()	const
	{
		return m_bEnable == true;
	}

	bool IsDisable()	const
	{
		return m_bEnable == false;
	}

	bool IsActive()	const
	{
		return m_bActive;
	}

	int GetRefCount()	const
	{
		return m_iRefCount;
	}

	const std::string& GetName()	const
	{
		return m_strName;
	}
};

