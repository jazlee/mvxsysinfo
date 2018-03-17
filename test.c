#include <pthread.h>
#include <syscall.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <math.h>
#include <sys/time.h>
#include <sys/times.h>
#include <sys/param.h>
#include <uuid/uuid.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <sys/resource.h>
#include <sys/sysinfo.h>
#include <stdio.h>

extern char **environ;

struct pstat {
    long unsigned int utime_ticks;
    long int cutime_ticks;
    long unsigned int stime_ticks;
    long int cstime_ticks;
    long unsigned int vsize; // virtual memory size in bytes
    long unsigned int rss; //Resident  Set  Size in bytes

    long unsigned int cpu_total_time;
    struct timeval time_value;
};


int get_total_usage(struct pstat* result) {
    int i;

    FILE *fstat = fopen("/proc/stat", "r");
    if (fstat == NULL) {
        perror("FOPEN ERROR ");
        fclose(fstat);
        return -1;
    }

    //read+calc cpu total time from /proc/stat
    long unsigned int cpu_time[10];
    bzero(cpu_time, sizeof (cpu_time));
    if (fscanf(fstat, "%*s %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu",
            &cpu_time[0], &cpu_time[1], &cpu_time[2], &cpu_time[3],
            &cpu_time[4], &cpu_time[5], &cpu_time[6], &cpu_time[7],
            &cpu_time[8], &cpu_time[9]) == EOF) {
        fclose(fstat);
        return -1;
    }

    fclose(fstat);
    result->utime_ticks = cpu_time[0] + cpu_time[1] + cpu_time[2];
    result->cutime_ticks = 0;
    result->stime_ticks = 0;
    result->cstime_ticks = 0;
    result->cpu_total_time = 0;
    for (i = 0; i < 6; i++)
        result->cpu_total_time += cpu_time[i];

    return 0;
}

void main()
{

    struct pstat b_usage, e_usage;
    double idle_delta, total_delta;
    long int total, i, calc;

    get_total_usage(&b_usage);
    calc = 0;
    for (i =0; i<20000000;i++)
        calc = calc + i;
    get_total_usage(&e_usage);
    idle_delta = e_usage.utime_ticks - b_usage.utime_ticks;
    total_delta = e_usage.cpu_total_time - b_usage.cpu_total_time;
    // total = 100 * (1.0 - idle_delta/total_delta);         
    total = (idle_delta / total_delta) * 100;
    printf("CPU Usage: ((%d - %d)/(%d - %d))*100= %d\n", 
        e_usage.utime_ticks, b_usage.utime_ticks, 
        e_usage.cpu_total_time, b_usage.cpu_total_time,total);
}

