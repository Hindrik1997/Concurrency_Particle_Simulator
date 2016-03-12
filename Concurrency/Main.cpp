#include "Threadpool.h"
#include "Task.h"
#include "ManagedTask.h"

int main()
{
	Threadpool pool(8);
	ManagedTask::SetDefaultPool(pool);

	std::function<void()> lambda = []() { std::cout << "Hello from work item " << std::endl; };
	Task t(lambda);
	pool.Enqueue(t);
	
	std::cin.get();
	return 0;
}