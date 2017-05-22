#pragma once

const int WIDTH = 800;
const int HEIGHT = 600;

// Standard Values for Number of Points
extern int NUMBEROFPOINTS;
extern bool StepbyStep;

const int POINTRADIUS = 2;
const int POINTHULLRADIUS = 5;

struct timeMeasure
{
	int hours = 0;
	int minutes = 0;
	int seconds = 0;
	int milliseconds = 0;

	timeMeasure operator+(timeMeasure rhs)
	{
		this->hours += rhs.hours;
		this->minutes += rhs.minutes;
		this->seconds += rhs.seconds;
		this->milliseconds += rhs.milliseconds;
		return (*this);
	}
	timeMeasure operator/(int factor)
	{
		this->hours = this->hours / factor;
		this->minutes = this->minutes / factor;
		this->seconds = this->seconds / factor;
		this->milliseconds = this->milliseconds / factor;
		return (*this);
	}
	timeMeasure()
	{
	}
};