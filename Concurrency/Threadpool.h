#pragma once
#include <deque>
#include <thread>
#include <condition_variable>
#include <vector>
#include "Worker.h"

//Task interface base class
class ITask;
//Temporary managed task
class ManagedTask;

class Threadpool {
public:
	Threadpool(size_t threads);
	//Do not pas a temporary object in here!
	void Enqueue(ITask* job);
	void Enqueue(ManagedTask job);

	~Threadpool();
private:
	friend class Worker;
	std::vector<std::thread> m_Workers;
	std::deque<ITask*> m_Tasks;
	std::condition_variable m_Cond;
	std::mutex m_Queue_Mutex;
	bool m_Stop;
};