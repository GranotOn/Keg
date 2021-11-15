#pragma once

struct Time
{
	double deltaTime;
	double timeStamp;

	Time() : deltaTime(0), timeStamp(0) {}
	Time(double ts, double dt) : deltaTime(dt), timeStamp(ts) {}

	double operator-(double time) { return time - timeStamp; }
};