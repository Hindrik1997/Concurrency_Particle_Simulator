#pragma once
#include <mutex>
#include <thread>
#include <vector>
#include <deque>
#include <iostream>

class Threadpool;

class Worker {
public:
	Worker(Threadpool &s) : m_Pool(s) { }
	void operator()();
private:
	Threadpool& m_Pool;
};