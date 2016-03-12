#pragma once
#include "ITask.h"

class Threadpool;

class ManagedTask
{
public:
	ManagedTask(Threadpool& pool);
	ManagedTask();
	~ManagedTask();
	static void SetDefaultPool(Threadpool& pool);
	static void InvalidateDefaultPool();
private:
	Threadpool& m_Pool;
	static Threadpool* m_DefaultPool;
};

