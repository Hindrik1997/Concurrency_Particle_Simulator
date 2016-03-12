#include "Worker.h"
#include "Threadpool.h"
#include "ITask.h"

void Worker::operator()()
{
	ITask* task;
	while (true)
	{
		std::unique_lock<std::mutex> locker(m_Pool.m_Queue_Mutex);
		m_Pool.m_Cond.wait(locker, [this]() -> bool { return !m_Pool.m_Tasks.empty() || m_Pool.m_Stop; });
			if (m_Pool.m_Stop)
				return;
			if (!m_Pool.m_Tasks.empty())
			{
				task = m_Pool.m_Tasks.front();
				m_Pool.m_Tasks.pop_front();
				locker.unlock();
				(*task)();
			}
		else {
			locker.unlock();
		}
	}
}