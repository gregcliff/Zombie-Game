//Dr. Ramsey's Timer class without the namespace

#ifndef TIMER_H_RAMSEY55
#define TIMER_H_RAMSEY55

#include <ctime>

class Timer {
public:
	clock_t start;
	Timer() { start = clock(); }
	double elapsed() { return 1000*(clock() - start) / (double)CLOCKS_PER_SEC; }
	void restart() { start = clock(); }
};

#endif