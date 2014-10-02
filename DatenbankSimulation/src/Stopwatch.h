#ifndef STOPWATCH_H_
#define STOPWATCH_H_

#include <vector>
#include <fstream>


class Stopwatch
{
public:
	Stopwatch(unsigned int);
	virtual ~Stopwatch();

	void start();
	void lap();
	void stop();
	double getLapTime(unsigned int lap);
	double getTotalTime();
	size_t getSize();
private:
	std::vector<double> lapTimeList;
	double startTime;
};



#endif /* STOPWATCH_H_ */
