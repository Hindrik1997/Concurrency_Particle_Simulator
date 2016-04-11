#include "Particle.h"
#include <algorithm>

Particle::Particle(int xT, int yT, float xVeloc, float yVeloc, COLORREF colorT, int _TimeToLive) : xPosition(xT), yPosition(yT), xVelocity(xVeloc), yVelocity(yVeloc), color(colorT), TimeToLive(_TimeToLive)
{
}

Particle::~Particle()
{
}

void Particle::operator()() {
	TimeToLive--;
	
	for (int x = -size; x <= size; ++x)
	{
		for (int y = -size; y <= size; ++y)
		{
			if (xPosition + x > 0 && xPosition + x < WIDTH && yPosition + y > 0 && yPosition + y < HEIGHT)
				ScreenBuffer[xPosition + x][yPosition + y] = RGB(0, 0, 0);
		}
	}

	xPosition += xVelocity;
	yPosition += yVelocity;

	if (xPosition <= 0 || xPosition >= WIDTH)
		xVelocity = -xVelocity;
	if (yPosition <= 0 || yPosition >= HEIGHT)
		yVelocity = -yVelocity;


	for (int x = -size; x <= size; ++x)
	{
		for (int y = -size; y <= size; ++y)
		{
			if (xPosition + x > 0 && xPosition + x < WIDTH && yPosition + y > 0 && yPosition + y < HEIGHT)
				ScreenBuffer[xPosition + x][yPosition + y] = color;
		}
	}
};