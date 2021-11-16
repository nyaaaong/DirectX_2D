#pragma once

template <typename T>
class CSharedPtr
{
public:
	CSharedPtr()	:
		m_pPtr(nullptr)
	{
	}

	CSharedPtr(const CSharedPtr<T>& pPtr)
	{
		m_pPtr = pPtr.m_pPtr;

		if (m_pPtr)
			m_pPtr->AddRef();
	}

	~CSharedPtr()
	{
		if (m_pPtr)
			m_pPtr->Release();
	}

private:
	T* m_pPtr;

public:
	void operator = (const T& pPtr)
	{
		if (m_pPtr)
			m_pPtr->Release();

		m_pPtr = pPtr;

		if (m_pPtr)
			m_pPtr->AddRef();
	}

	void operator = (const CSharedPtr<T>& pPtr)
	{
		if (m_pPtr)
			m_pPtr->Release();

		m_pPtr = pPtr.m_pPtr;

		if (m_pPtr)
			m_pPtr->AddRef();
	}

	bool operator == (const T& pPtr)	const
	{
		return m_pPtr == pPtr;
	}

	bool operator == (const CSharedPtr<T>& pPtr)	const
	{
		return m_pPtr == pPtr.m_pPtr;
	}

	bool operator != (const T& pPtr)	const
	{
		return m_pPtr != pPtr;
	}

	bool operator != (const CSharedPtr<T>& pPtr)	const
	{
		return m_pPtr != pPtr.m_pPtr;
	}

	operator T* ()	const
	{
		return m_pPtr;
	}

	T* operator -> ()	const
	{
		return m_pPtr;
	}
};

