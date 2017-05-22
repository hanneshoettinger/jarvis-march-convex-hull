#pragma once
#include <vector>
#include <Windows.h>
#include "globaldef.h"
class Timer {
public:
	Timer();
	~Timer();
	void startTimer();
	void stopTimer(char);
	void saveTimes(const char*);
private:
	timeMeasure times;
	timeMeasure calculateTimeAverage(std::vector<timeMeasure> times);
	LARGE_INTEGER frequency;        // ticks per second
	LARGE_INTEGER t1, t2;           // ticks
	double elapsedTime;
	std::vector<timeMeasure>  Times;
	std::vector<timeMeasure>  TimesX;
	std::vector<timeMeasure>  TimesY;
};