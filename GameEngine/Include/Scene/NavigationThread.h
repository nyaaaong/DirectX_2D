#pragma once

#include "../Thread.h"
#include "../ThreadQueue.h"

// ������ 1���� ��ã�� �˰����� �����Ѵ�.
class CNavigationThread :
	public CThread
{
	friend class CNavigationManager;

public:
	CNavigationThread();
	virtual ~CNavigationThread();

private:
	class CNavigationManager* m_NavManager;
	CThreadQueue<NavWorkData>			m_WorkQueue;
	class CNavigation* m_Navigation;
	HANDLE				m_ExitEvent;

public:
	void Clear()
	{
		m_WorkQueue.clear();
	}

public:
	int GetWorkCount()
	{
		return m_WorkQueue.size();
	}

	void CreateNavigationNode(class CTileMapComponent* TileMap);

public:
	virtual void Run();

	template <typename T>
	void AddWork(T* Obj, void(T::* Func)(const std::list<Vector3>&), const Vector3& Start, const Vector3& End)
	{
		NavWorkData	Data;
		Data.Callback = std::bind(Func, Obj, std::placeholders::_1);
		Data.Start = Start;
		Data.End = End;

		m_WorkQueue.push(Data);
	}
};

