#pragma once
#include "Timer.h"
#include <stdio.h>

Timer::Timer()
{
}

Timer::~Timer()
{
}

void Timer::startTimer()
{
	// get ticks per second
	QueryPerformanceFrequency(&frequency);

	// start timer
	QueryPerformanceCounter(&t1);
}

void Timer::stopTimer(char select)
{
	// stop timer
	QueryPerformanceCounter(&t2);

	// compute the elapsed time
	elapsedTime = (t2.QuadPart - t1.QuadPart) * 1000.0 / frequency.QuadPart;

	int milliseconds = (int)(elapsedTime) % 1000;
	int seconds = (int)(elapsedTime / 1000) % 60;
	int minutes = (int)(elapsedTime / (1000 * 60)) % 60;
	int hours = (int)(elapsedTime / (1000 * 60 * 60)) % 24;

	printf("%.2d:%.2d:%.2d.%.3d; \n", hours, minutes, seconds, milliseconds);

	timeMeasure temp;
	temp.hours = hours;
	temp.minutes = minutes;
	temp.seconds = seconds;
	temp.milliseconds = milliseconds;
	switch (select)
	{
	case ' ':
		Times.push_back(temp);
		break;
	case 'X':
		TimesX.push_back(temp);
		break;
	case 'Y':
		TimesY.push_back(temp);
		break;
	default:
		break;
	}
	

	elapsedTime = 0;
}
void Timer::saveTimes(const char* filename)
{
	using namespace std;
	
	timeMeasure avergae;
	timeMeasure avergaeX;
	timeMeasure avergaeY;

	avergae = calculateTimeAverage(Times);
	avergaeX = calculateTimeAverage(TimesX);
	avergaeY = calculateTimeAverage(TimesY);

	FILE * pFile;

	fopen_s(&pFile,filename,"w");
	fprintf(pFile, "Timeformat: hh:mm:ss.ms\n");
	fprintf(pFile, "Average Time for Jarvis Algorithm: %.2d:%.2d:%.2d.%.3d\n", avergae.hours, avergae.minutes, avergae.seconds, avergae.milliseconds);
	fprintf(pFile, "Average Time for Jarvis Algorithm Special Case Line on X Axis: %.2d:%.2d:%.2d.%.3d\n", avergaeX.hours, avergaeX.minutes, avergaeX.seconds, avergaeX.milliseconds);
	fprintf(pFile, "Average Time for Jarvis Algorithm Special Case Line on Y Axis: %.2d:%.2d:%.2d.%.3d\n", avergaeY.hours, avergaeY.minutes, avergaeY.seconds, avergaeY.milliseconds);

	fclose(pFile);
}
timeMeasure Timer::calculateTimeAverage(std::vector<timeMeasure> times)
{
	timeMeasure temp;
	for (timeMeasure n : times)
	{
		temp = temp + n;
	}
	return temp / times.size();
}