#pragma once
class StatsCounter
{
public:
	StatsCounter();
	~StatsCounter();

	void		 AddValue(unsigned int value);
	unsigned int GetAverage();
	unsigned int GetCount();
	unsigned int GetMinimum();
	unsigned int GetMaximum();

	void DumpValues();

private:
	unsigned int		_minimum;
	unsigned int		_maximum;
	unsigned __int64	_total;
	unsigned int		_count;
};

