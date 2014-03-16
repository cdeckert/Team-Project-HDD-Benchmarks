#ifndef ZONED_H_
#define ZONED_H_

#include "Benchmark.h"

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
			int diskSize;
			int largeSize;
			int reportSize;
			char * buffer;
			void measureSize();
	};

} /* namespace Benchmark */

#endif /* ZONED_H_ */
