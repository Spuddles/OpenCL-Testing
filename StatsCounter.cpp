#include "StatsCounter.h"
#include <iostream>

StatsCounter::StatsCounter():
	 _minimum(-1)
	,_maximum(0)
	,_total(0)
	,_count(0)
{
}

StatsCounter::~StatsCounter()
{
}

void StatsCounter::AddValue(unsigned int value)
{
	_total += value;
	_count++;

	if (value < _minimum)
	{
		_minimum = value;
	}

	if (value > _maximum)
	{
		_maximum = value;
	}
}

unsigned int StatsCounter::GetAverage()
{
	if (_count > 0)
		return static_cast<unsigned int>(_total / _count);
	else
		return 0;
}

unsigned int StatsCounter::GetCount()
{
	return _count;
}

unsigned int StatsCounter::GetMinimum()
{
	return _minimum;
}

unsigned int StatsCounter::GetMaximum()
{
	return _maximum;
}

void StatsCounter::DumpValues()
{
	std::cout << "Count:" << _count;
	std::cout << " Min:" << _minimum;
	std::cout << " Max:" << _maximum;
	std::cout << " Avg:" << GetAverage();
	std::cout << std::endl;
}