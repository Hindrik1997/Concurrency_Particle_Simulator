#pragma once

class ITask
{
public:
	virtual void operator()() = 0;
};