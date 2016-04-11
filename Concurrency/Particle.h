#pragma once
#include <thread>
#include <chrono>
#include <iostream>
#include "ITask.h"
#include <cmath>
#include <vector>
#include "WindowFunctions.h"
# define PI           3.14159265358979323846

using std::vector;

class Particle : public ITask
{
public:
	int xPosition = 0;
	int yPosition = 0;

	float xVelocity = 0.0f;
	float yVelocity = 0.0f;

	int size = 0;
	int TimeToLive = 0;

	COLORREF color;

	void operator()();

	Particle(int xT, int yT, float xVeloc, float yVeloc,COLORREF colorT, int TimeToLive);
	~Particle();
};

