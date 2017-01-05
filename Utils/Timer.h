#pragma once
#include <chrono>

class Timer
{
public:
						Timer();
						~Timer();
	static void			startTimer();
	static unsigned int	getTimer();
private:
	static std::chrono::high_resolution_clock::time_point _start;
};

