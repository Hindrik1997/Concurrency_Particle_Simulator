#include "ManagedTask.h"
#include "Threadpool.h"

Threadpool* ManagedTask::m_DefaultPool = nullptr;

ManagedTask::ManagedTask(Threadpool& pool, ITask* task) : m_Pool(&pool), m_Task(task)
{
}

ManagedTask::ManagedTask(ITask* task) : m_Pool(&*m_DefaultPool), m_Task(task)
{
	if (m_DefaultPool == nullptr)
		throw("If using the default ManagedTask constructor, the default threadpool may not be nullptr");
}


ManagedTask::~ManagedTask()
{
}