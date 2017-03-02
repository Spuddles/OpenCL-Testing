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

std::chrono::system_clock::time_point Timer::getCurrentTime()
{
	return std::chrono::system_clock().now();
}

float Timer::getDuration(std::chrono::system_clock::time_point start)
{
	// Get the current time and subtract our orginal time to get the duration
	std::chrono::system_clock::time_point tp = std::chrono::system_clock().now();

	std::chrono::milliseconds duration = std::chrono::duration_cast<std::chrono::milliseconds>(tp - start);

	return static_cast<float>(duration.count());
}

void Timer::sleepMS(unsigned int ms)
{
	std::chrono::system_clock::time_point now = std::chrono::system_clock().now();

	std::chrono::system_clock::time_point end = now + std::chrono::milliseconds(ms);

	while (end > now)
	{
		now = std::chrono::system_clock().now();
	}
}