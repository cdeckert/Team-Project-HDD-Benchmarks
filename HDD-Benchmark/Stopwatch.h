#ifndef STOPWATCH_H_
#define STOPWATCH_H_

#include <vector>


class Stopwatch {
public:
	Stopwatch(int);
	virtual ~Stopwatch();

	void start();
	void lap();
	void stop();
	double getLapTime(int lap);
	double getTotalTime();
private:
	std::vector<double> lapTimeList;
	double startTime;
};



#endif /* STOPWATCH_H_ */
