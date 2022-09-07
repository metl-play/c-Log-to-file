// log.h; the header file which defines Log(); and LogErr();
// Can use %d, %f, %s, x%

#include <stdio.h>
#include <stdarg.h>
#include <time.h>

//#define LOGFILE "log.txt" // all Log(); messages will be appended to this file (OLD)!
#define true 1
#define false 0

#define F_OK 0
#define access _access

_Bool LogCreated; // keeps track whether the log file is created or not
_Bool normalTime; // used for the timestamp format hh:mm:ss or unix

void Log(char *message, ...); // logs a message to LOGFILE

void LogErr(char* message, ...); // logs a message; execution is interrupted


_Bool LogCreated = false;
_Bool normalTime = true;

//void Log(char *message)
void Log(char* message, ...)
{
	/*todo:
	log to %temp% directory in Windows*/
	//log dir

	//logfile name defined by time and date
	time_t rawtime = time(NULL);
	struct tm* ptm = localtime(&rawtime);

	int time_day = ptm->tm_mday;  // day of the month - [1, 31]
	char stime_day[3];
	sprintf(stime_day, "%02d", time_day);

	int time_mon = ptm->tm_mon + 1;   // months since January - [1, 12]
	char stime_mon[3];
	sprintf(stime_mon, "%02d", time_mon);

	int time_hour = ptm->tm_hour;  // hours since midnight - [0, 23]
	char stime_hour[3];
	sprintf(stime_hour, "%02d", time_hour);

	char logfile[11];
	strcpy(logfile, stime_mon);
	strcat(logfile, stime_day);
	strcat(logfile, stime_hour);
	strcat(logfile, ".txt");	// every file extension will work, the file still need to be opned in text mode

	FILE *file;

	if (_access(logfile, F_OK) == 0) {
		// file exists
		file = fopen(logfile, "a");
	}
	else {
		// file doesn't exist
		file = fopen(logfile, "w");
		LogCreated = true;
	}

	if (file == NULL)
	{
		LogCreated = false;
		return;
	}
	else
	{
		if (normalTime == true)
		{
			if (strlen(message) >0) {
				// Zeit Tracking
				time_t rawtime = time(NULL);

				if (rawtime == -1)
				{
					fputs("The time() function failed", file);
				}

				struct tm* ptm = localtime(&rawtime);

				if (ptm == NULL)
				{
					fputs("The localtime() function failed", file);
				}

				int time_day = ptm->tm_mday;  // day of the month - [1, 31]
				char stime_day[3];
				sprintf(stime_day, "%02d", time_day);

				int time_mon = ptm->tm_mon + 1;   // months since January - [1, 12]
				char stime_mon[3];
				sprintf(stime_mon, "%02d", time_mon);

				int time_year = ptm->tm_year + 1900;  // years since 0
				//int time_year = ptm->tm_year-100;  // years since 2000
				char stime_year[5];
				sprintf(stime_year, "%02d", time_year);

				//normal time for hh mm ss
				int time_hour = ptm->tm_hour;  // hours since midnight - [0, 23]
				char stime_hour[3];
				sprintf(stime_hour, "%02d", time_hour);

				int time_min = ptm->tm_min;   // minutes after the hour - [0, 59]
				char stime_min[3];
				sprintf(stime_min, "%02d", time_min);

				int time_sec = ptm->tm_sec;   // seconds after the minute - [0, 60] including leap second
				char stime_sec[3];
				sprintf(stime_sec, "%02d", time_sec);

				//Log string
				fputs("[", file);
				fputs(stime_day, file);
				fputs(".", file);
				fputs(stime_mon, file);
				fputs(".", file);
				fputs(stime_year, file);
				fputs(" ", file);
				fputs(stime_hour, file);
				fputs(":", file);
				fputs(stime_min, file);
				fputs(":", file);
				fputs(stime_sec, file);
				fputs("] ", file);
			}

			va_list args;
			va_start(args, message);
			vfprintf(file, message, args);
			va_end(args);

			fputs("\n", file);

			fclose(file);
		}
		else if(normalTime == false)
		{
			if (strlen(message) > 0) {
				//unix time
				unsigned long int utimes = (unsigned long)time(NULL);
				char sutimes[11];
				sprintf(sutimes, "%10d", utimes);

				fputs("[", file);
				fputs(sutimes, file);
				fputs("] ", file);
			}

			va_list args;
			va_start(args, message);
			vfprintf(file, message, args);
			va_end(args);

			fputs("\n", file);

			fclose(file);
		}
		else
		{
			fputs(message, file);
			fputs("\n", file);

			fclose(file);
		}
	}
	if (file) fclose(file);
}

void LogErr(char* message)
{
	Log(message);
}