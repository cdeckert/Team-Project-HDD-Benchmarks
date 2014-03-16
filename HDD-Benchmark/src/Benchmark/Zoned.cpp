#include <Zoned.h>
#include "Stopwatch.h"

#include <cmath>
namespace Benchmark
{

	Zoned::Zoned(std::string theAddress): Benchmark(theAddress)
	{
		this->fd = open64(theAddress.data(), O_RDWR | O_SYNC); //, O_DIRECT, O_LARGEFILE);
		perror("open");
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
		int iterations = round(diskSize / reportSize);

		printf("iterations: %d", iterations);
		Stopwatch stopwatch = Stopwatch(iterations);
		int transfer = 0;
		int lap = 0;
		while(read(fd, buffer, largeSize) == largeSize)
		{

			transfer += largeSize;
			if(transfer >= reportSize)
			{
				//perror("read");
				lap++;
				std::cout << "\r LAP:" << lap << ":"<< iterations << ":" << round(lap*10000/iterations)/1000;
				stopwatch.lap();
				transfer = 0;
			}
		}
		stopwatch.stop();
	}

	void Zoned::measureSize()
	{
		lseek64(fd, 0L, SEEK_SET);
		this->diskSize = lseek64(fd, 0L, SEEK_END);
		std::cout << diskSize << "DISK\n";
		lseek64(fd, 0L, SEEK_SET);
	}


	Zoned::~Zoned() {
		// TODO Auto-generated destructor stub
	}

} /* namespace Benchmark */
