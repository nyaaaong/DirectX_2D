#pragma once

#include "../Thread.h"
#include "../ThreadQueue.h"

// 쓰레드 1개가 길찾기 알고리즘을 수행한다.
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
	bool			m_Process;

public:
	void SetProcess(bool Process)
	{
		m_Process = Process;
	}

public:
	int GetWorkCount()
	{
		return m_WorkQueue.size();
	}

	void Stop(size_t ObjTypeID)
	{
		int Size = m_WorkQueue.size();

		for (int i = 0; i < Size; ++i)
		{
			NavWorkData Data = m_WorkQueue.front();

			//if (Data.TypeID == ObjTypeID)

		}
	}

	void CreateNavigationNode(class CTileMapComponent* TileMap);

public:
	virtual void Run();

	template <typename T>
	void AddWork(T* Obj, void(T::* Func)(const std::list<Vector3>&), const Vector3& Start, const Vector3& End)
	{
		NavWorkData	Data;
		Data.Callback = std::bind(Func, Obj, std::placeholders::_1);
		Data.TypeID = Obj->GetTypeID();
		Data.Start = Start;
		Data.End = End;

		m_WorkQueue.push(Data);
	}
};

