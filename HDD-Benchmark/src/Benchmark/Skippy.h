#ifndef SKIPPY_H
#define	SKIPPY_H

#include "Benchmark.h"
#include "ResultSaver.h"

namespace Benchmark
{

	class Skippy : public Benchmark
	{
		public:
			Skippy(std::string);
			void configure(int, int, int);
			void runIteration(int);
			void execute();
			virtual ~Skippy();


		private:
			int iterations;
			int fd;
			int singleSector;
			char * buffer;
	};
}
#endif	/* SKIPPY_H */

