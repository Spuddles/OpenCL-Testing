#include "Timer.h"

std::chrono::high_resolution_clock::time_point Timer::_start;

Timer::Timer()
{
}

Timer::~Timer()
{
}

void Timer::startTimer()
{
	_start = std::chrono::high_resolution_clock::now();
}

unsigned int Timer::getTimer()
{
	std::chrono::high_resolution_clock::time_point _end = std::chrono::high_resolution_clock::now();

	std::chrono::microseconds us = std::chrono::duration_cast<std::chrono::microseconds>(_end - _start);

	return static_cast<unsigned int>(us.count());
}
