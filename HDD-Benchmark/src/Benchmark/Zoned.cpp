#include <Zoned.h>
#include "Stopwatch.h"

#include <cmath>
namespace Benchmark
{

	Zoned::Zoned(std::string theAddress): Benchmark(theAddress)
	{
		this->fd = open64(theAddress.data(), O_RDWR | O_SYNC); //, O_DIRECT, O_LARGEFILE);
		perror("open");
		printf("FD %d",fd);
		measureSize();
	}

	void Zoned::configure(int bufferSize, int largeSize, int reportSize)
	{
		this->largeSize = largeSize;
		char* b = new char[bufferSize];
		this->buffer = b;
		this->reportSize = reportSize;
		perror("config");
	}

	void Zoned::execute()
	{
		int iterations = round(this->diskSize / this->reportSize);
		Stopwatch stopwatch = Stopwatch(iterations);
		int transfer = 0;
		int lap = 0;
		while(read(fd, buffer, largeSize) == largeSize && lap < 10000)
		{

			transfer += largeSize;
			if(transfer >= reportSize)
			{
				//perror("read");
				lap++;
				std::cout << "\r" << iterations << ":" << lap << "\n";
				stopwatch.lap();
				transfer = 0;
			}
		}
		stopwatch.stop();
	}

	void Zoned::measureSize()
	{
		this->diskSize = lseek64(fd, 0L, SEEK_END);
		lseek64(fd, 0L, SEEK_SET);
	}


	Zoned::~Zoned() {
		// TODO Auto-generated destructor stub
	}

} /* namespace Benchmark */
