/*
 * Stopwatch.cpp
 *
 *  Created on: Mar 7, 2014
 *      Author: christiandeckert
 */

#include "Stopwatch.h"

#if defined(_WIN32)
#include <Windows.h>

#elif defined(__unix__) || defined(__unix) || defined(unix) || (defined(__APPLE__) && defined(__MACH__))
#include <unistd.h>	/* POSIX flags */
#include <time.h>	/* clock_gettime(), time() */
#include <sys/time.h>	/* gethrtime(), gettimeofday() */
#include <math.h>


#if defined(__MACH__) && defined(__APPLE__)
#include <mach/mach.h>
#include <mach/mach_time.h>
#endif

#else
#error "Unable to define getRealTime( ) for an unknown OS."
#endif

static double getTime()
{
#if defined(_WIN32)
		FILETIME tm;
		ULONGLONG t;
	#if defined(NTDDI_WIN8) && NTDDI_VERSION >= NTDDI_WIN8
		/* Windows 8, Windows Server 2012 and later. ---------------- */
		GetSystemTimePreciseAsFileTime( &tm );
	#else
		/* Windows 2000 and later. ---------------------------------- */
		GetSystemTimeAsFileTime( &tm );
	#endif
		t = ((ULONGLONG)tm.dwHighDateTime << 32) | (ULONGLONG)tm.dwLowDateTime;
		return (double)t / 10000000.0;

	#elif (defined(__hpux) || defined(hpux)) || ((defined(__sun__) || defined(__sun) || defined(sun)) && (defined(__SVR4) || defined(__svr4__)))
		/* HP-UX, Solaris. ------------------------------------------ */
		return (double)gethrtime( ) / 1000000000.0;

	#elif defined(__MACH__) && defined(__APPLE__)
		/* OSX. ----------------------------------------------------- */
		static double timeConvert = 0.0;
		if ( timeConvert == 0.0 )
		{
			mach_timebase_info_data_t timeBase;
			(void)mach_timebase_info( &timeBase );
			timeConvert = (double)timeBase.numer /
				(double)timeBase.denom /
				1000000000.0;
		}
		return (double)mach_absolute_time( ) * timeConvert;

	#elif defined(_POSIX_VERSION)
		/* POSIX. --------------------------------------------------- */
	#if defined(_POSIX_TIMERS) && (_POSIX_TIMERS > 0)
		{
			struct timespec ts;
	#if defined(CLOCK_MONOTONIC_PRECISE)
			/* BSD. --------------------------------------------- */
			const clockid_t id = CLOCK_MONOTONIC_PRECISE;
	#elif defined(CLOCK_MONOTONIC_RAW)
			/* Linux. ------------------------------------------- */
			const clockid_t id = CLOCK_MONOTONIC_RAW;
	#elif defined(CLOCK_HIGHRES)
			/* Solaris. ----------------------------------------- */
			const clockid_t id = CLOCK_HIGHRES;
	#elif defined(CLOCK_MONOTONIC)
			/* AIX, BSD, Linux, POSIX, Solaris. ----------------- */
			const clockid_t id = CLOCK_MONOTONIC;
	#elif defined(CLOCK_REALTIME)
			/* AIX, BSD, HP-UX, Linux, POSIX. ------------------- */
			const clockid_t id = CLOCK_REALTIME;
	#else
			const clockid_t id = (clockid_t)-1;	/* Unknown. */
	#endif /* CLOCK_* */
		//	if ( id != (clockid_t)-1 && clock_gettime( id, &ts ) != -1 )
		//		return (double)ts.tv_sec +
		//			(double)ts.tv_nsec / 1000000000.0;
			/* Fall thru. */
		}
	#endif /* _POSIX_TIMERS */

		/* AIX, BSD, Cygwin, HP-UX, Linux, OSX, POSIX, Solaris. ----- */
		struct timeval tm;
		gettimeofday( &tm, NULL );
		return (double)tm.tv_sec + (double)tm.tv_usec / 1000000.0;
	#else
		return -1.0;		/* Failed. */
	#endif
}

Stopwatch::Stopwatch(unsigned int iterations) {
	lapTimeList.reserve(iterations);
    startTime = -1;
    perror("Stopwatch");
}

void Stopwatch::start()
{
	startTime = getTime();
}

void Stopwatch::stop()
{

}

void Stopwatch::lap()
{
	if(startTime==-1) start();
	lapTimeList.push_back(getTime()-startTime);
	start();
}

double Stopwatch::getLapTime(unsigned int lap)
{
	if(lap < lapTimeList.size())
	{
		return lapTimeList.at(lap);
	}
	else
	{
		return -1;
	}
}

double Stopwatch::getTotalTime()
{
	double sum = 0;
        
	for(int i=0; i < (lapTimeList.size()); i++)
	{
		sum+= getLapTime(i);
	}
	return sum;
}




Stopwatch::~Stopwatch() {
	// TODO Auto-generated destructor stub
}

size_t Stopwatch::getSize()
{
	return lapTimeList.size();
}



