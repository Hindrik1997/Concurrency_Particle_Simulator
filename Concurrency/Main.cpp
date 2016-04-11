#include "Threadpool.h"
#include "Task.h"
#include <string>
#include <vector>
#include "WindowFunctions.h"
#include <thread>
#include "Particle.h"
#include <random>
#include <iostream>
#include <limits>

using std::cout;
using std::cin;
using std::endl;
using std::wstring;

HWND gHwnd = NULL;

std::string GetLine()
{
	std::string str;
	std::getline(std::cin, str);
	return str;
}

int main()
{
	long long ParticleCount = 10000;
	bool AsFastAsPossible = false;
	bool UseThreadpool = false;

	cout << "This application is meant to illustrate what happens when you use maaaanyyy small tasks on a threadpool. \n a threadpool therefore is not always a good choice. \n The queueing overhead will kill the performance. Please use 1-10 million particles for this effect. \n The non threadpool variant will handle this easily, whereas the pooled variant won't" << endl;

	ReAsk:
	cout << "How many particles do you want?";
	cin >> ParticleCount;
	if (cin.fail() || ParticleCount < 100 || ParticleCount > 10000000)
	{
		cin.clear();
		cin.ignore();
		cout << "Please enter a valid number betweet 100 and 10 million" << endl;
		goto ReAsk;
	}

		ReAsk2:
	cout << "Do you want to let the particles go as fast as they can? (If not they will be locked at 60fps) [1/0]";
	cin >> AsFastAsPossible;
	if (cin.fail())
	{
		cin.clear();
		cin.ignore();
		cout << "Please enter a 1 for yes and a 0 for false" << endl;
		goto ReAsk2;
	}

	ReAsk3:
	cout << "Do you want to use a threadpool? [1/0]";
	cin >> UseThreadpool;
	if (cin.fail())
	{
		cin.clear();
		cin.ignore();
		cout << "Please enter a 1 for yes and a 0 for false" << endl;
		goto ReAsk3;
	}

	Threadpool pool(_Thrd_hardware_concurrency());


	std::default_random_engine gen;
	std::uniform_int_distribution<int> PosDistX(0, WIDTH);
	std::uniform_int_distribution<int> ColorDist(1, 255);
	std::uniform_int_distribution<int> PosDistY(0, HEIGHT);
	std::uniform_real_distribution<float> Angle(0,360);
	std::uniform_real_distribution<float> Veloc(1,2);
	std::uniform_int_distribution<int> DirectionBoolean(0,1);
	
	wstring ClassName = { L"MT" };
	wstring WindowTitle = { L"MultiThreaded Particle System" };

	HINSTANCE hInstance = GetModuleHandle(NULL);

	gHwnd = InitializeWindow(hInstance, ClassName, WindowTitle, WIDTH, HEIGHT);
	if (gHwnd == NULL)
	{
		MessageBox(NULL, L"Window handle was zero?", L"Yo Dawg, Weird Error man!", MB_ICONEXCLAMATION | MB_OK);
		return -1;
	}

	ShowWindow(gHwnd, 1);
	UpdateWindow(gHwnd);

	//I like trains
	std::string train = R"(
      ====        ________                ___________
  _D _|  |_______/        \__I_I_____===__|_________|
   |(_)---  |   H\________/ |   |        =|___ ___|      _________________ 
   /     |  |   H  |  |     |   |         ||_| |_||     _|                \_____A
  |      |  |   H  |__--------------------| [___] |   =|                        |
  | ________|___H__/__|_____/[][]~\_______|       |   -|                        |
  |/ |   |-----------I_____I [][] []  D   |=======|____|________________________|_
__/ =| o |=-~~\  /~~\  /~~\  /~~\ ____Y___________|__|__________________________|_
 |/-=|___||    ||    ||    ||    |_____/~\___/          |_D__D__D_|  |_D__D__D_|
  \_/      \__/  \__/  \__/  \__/      \_/               \_/   \_/    \_/   \_/
		)";

	std::vector<Particle> particles;

	for (int i = 0; i < ParticleCount; i++)
	{
		particles.push_back(Particle(PosDistX(gen), PosDistY(gen), DirectionBoolean(gen) == 0 ? Veloc(gen) : -1 * Veloc(gen), DirectionBoolean(gen) == 0 ? Veloc(gen) : -1*Veloc(gen),RGB(ColorDist(gen),0,0),255));
	}

	int ThreadCount = _Thrd_hardware_concurrency() - 1;
	int ParticlesPerThreadCount = particles.size() / ThreadCount;
	bool MustStop = false;
	std::vector<std::thread> Threads;

	if (UseThreadpool == false)
	{
		for (int i = 0; i < ThreadCount; ++i)
		{
			Threads.push_back(std::thread([&ParticlesPerThreadCount, &particles, i, &MustStop, &AsFastAsPossible] {

				while (!MustStop)
				{
					for (int j = 0; j < ParticlesPerThreadCount; ++j)
					{
						particles[i * ParticlesPerThreadCount + j]();
					}
					if (!AsFastAsPossible)
						std::this_thread::sleep_for(std::chrono::milliseconds(16));
				}
			}));
		}
	}
	do
	{
		//Main loop met drawing enz. lekker bitblitten
		HDC hDC = GetDC(gHwnd);
		HDC hDCMem = CreateCompatibleDC(hDC);

		unsigned char* lpBitmapBits;

		BITMAPINFO bi;
		ZeroMemory(&bi, sizeof(BITMAPINFO));
		bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bi.bmiHeader.biWidth = WIDTH;
		bi.bmiHeader.biHeight = -HEIGHT;
		bi.bmiHeader.biPlanes = 1;
		bi.bmiHeader.biBitCount = 32;


		HBITMAP bitmap = CreateDIBSection(hDCMem, &bi, DIB_RGB_COLORS, (VOID**)&lpBitmapBits, NULL, 0);
		HGDIOBJ oldbmp = SelectObject(hDCMem, bitmap);

		BitBlt(hDCMem, 0, 0, WIDTH, HEIGHT, hDC, 0, 0, SRCCOPY);

		int pitch = 4 * WIDTH;
		int index;
		for (int x = 0; x < WIDTH; x = x++)
		{
			for (int y = 0; y < HEIGHT; y++)
			{
				index = y * pitch;
				index += x * 4;
				lpBitmapBits[index] = GetBValue(ScreenBuffer[x][y]);
				lpBitmapBits[index + 1] = GetGValue(ScreenBuffer[x][y]);
				lpBitmapBits[index + 2] = GetRValue(ScreenBuffer[x][y]);
			}
		}


		BitBlt(hDC, 0, 0, WIDTH, HEIGHT, hDCMem, 0, 0, SRCCOPY);

		SelectObject(hDCMem, oldbmp);
		DeleteDC(hDCMem);
		DeleteObject(bitmap);
		if (UseThreadpool == false)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(16)); //60 fps is voldoende voor t displayen
		}
		else
		{
			if (pool.GetSize() < 100)
			{
				for (int i = 0; i < ParticleCount; ++i)
				{
					pool.Enqueue(&particles[i]);
				}
			}
		}
	} while (CheckMessage() != false);
	if(UseThreadpool)
		pool.~Threadpool();
	else
	{
		MustStop = true;
		for (auto& t : Threads)
			t.join();
	}
	return 0;
}