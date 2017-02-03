#pragma once
#include <chrono>

class Timer
{
public:
						Timer();
						~Timer();

	// Methods for timing code execution 
	static void			startTimer();
	static unsigned int	getTimer();

	// System clock related functions to calculate the duration from a starting point
	static std::chrono::system_clock::time_point getCurrentTime();
	static float		getDuration(std::chrono::system_clock::time_point start);
	static void			sleepMS(unsigned int ms);

private:
	static std::chrono::high_resolution_clock::time_point _start;
};

