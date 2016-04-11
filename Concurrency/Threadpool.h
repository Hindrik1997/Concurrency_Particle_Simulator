#pragma once
#include <deque>
#include <thread>
#include <condition_variable>
#include "Worker.h"

//Task interface base class
class ITask;

class Threadpool {
public:
	Threadpool(size_t threads);
	//Do not pass a temporary object in here!
	void Enqueue(ITask* job);
	~Threadpool();
	void ClearDequeRam();
	inline int GetSize();
private:
	std::deque<ITask*> m_Tasks;
	std::vector<std::thread> m_Workers;
	std::condition_variable m_Cond;
	std::mutex m_Queue_Mutex;
	bool m_Stop;
	friend class Worker;
};

inline int Threadpool::GetSize() { return (int)m_Tasks.size();  }