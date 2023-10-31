#include "Timer.h"

using std::chrono::steady_clock;

Timer::Timer()
{
	last = steady_clock::now();
}

float Timer::Mark()
{
	const auto old = last;
	last = steady_clock::now();
	frameTime = last - old;
	return float(frameTime.count());

	
}
