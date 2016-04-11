#pragma once
#include "ITask.h"

class Threadpool;

class ManagedTask
{
public:
	ManagedTask(Threadpool& pool, ITask* task);
	ManagedTask(ITask* task);
	~ManagedTask();

	inline static void SetDefaultPool(Threadpool& pool);
	inline static void InvalidateDefaultPool();
	inline static Threadpool& GetDefaultPool();
	inline ITask* GetTask() const;
private:
	ITask* m_Task;
	Threadpool* m_Pool;
	static Threadpool* m_DefaultPool;
	bool m_SelfRemoval = false;
};

inline void ManagedTask::SetDefaultPool(Threadpool& pool) { m_DefaultPool = &pool; }
inline void ManagedTask::InvalidateDefaultPool() { m_DefaultPool = nullptr; }
inline Threadpool& ManagedTask::GetDefaultPool() { return *m_DefaultPool; }
inline ITask* ManagedTask::GetTask() const { return m_Task; };

/*
void Threadpool::Enqueue(ManagedTask Job)
{
std::unique_lock<std::mutex> lock(m_Queue_Mutex);
ManagedTask* t =new ManagedTask(Job);
m_ManagedTasks.push_back(*t);
m_Tasks.push_back(t->GetTask());
m_Cond.notify_one();
}*/