#pragma once
#include "ITask.h"
#include "ManagedTask.h"
#include <functional>
#include <memory>

using std::function;
using std::shared_ptr;

class Task : public ITask, public ManagedTask
{
public:
	Task(function<void()> task);
	~Task();
	function<void()> m_Task;
	void operator()();
};

