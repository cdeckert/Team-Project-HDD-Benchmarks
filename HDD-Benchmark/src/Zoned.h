#ifndef ZONED_H_
#define ZONED_H_

#include "Benchmark.h"
#include "ResultSaver.h"

namespace Benchmark
{

	class Zoned : public Benchmark
	{
		public:
			Zoned(std::string);
			void configure(int, int, int);
			void execute();
			virtual ~Zoned();
		private:
			int fd;
			off64_t diskSize;
			int largeSize;
			int reportSize;
			char * buffer;
			void measureSize();
			int iterations;
	};

} /* namespace Benchmark */

#endif /* ZONED_H_ */
