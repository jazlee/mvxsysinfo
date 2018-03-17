#include <jni.h>
#include <stdio.h>
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
#include "SysInfo.h"

extern char **environ;

static inline char *
skip_ws(const char *p) {
    while (isspace(*p)) p++;
    return (char *) p;
}

static inline char *
skip_token(const char *p) {
    while (isspace(*p)) p++;
    while (*p && !isspace(*p)) p++;
    return (char *) p;
}

JNIEXPORT jlong JNICALL
Java_systools_SysInfo_GetCurrentThreadId(JNIEnv *env, jobject obj) {
    pid_t thread_id = syscall(SYS_gettid);
    return thread_id;
}

JNIEXPORT jstring JNICALL
Java_systools_SysInfo_GetThreadIdString(JNIEnv *env, jobject obj, jlong paramLong) {
    char* name = (char*) calloc(1024, sizeof (char));
    if (name) {
        sprintf(name, "/proc/self/task/%ld/cmdline", paramLong);
        FILE* f = fopen(name, "r");
        if (f) {
            size_t size;
            size = fread(name, sizeof (char), 1024, f);
            if (size > 0) {
                if ('\n' == name[size - 1])
                    name[size - 1] = '\0';
            }
            fclose(f);
        }
    }
    return (*env)->NewStringUTF(env, name);
}

JNIEXPORT jlong JNICALL
Java_systools_SysInfo_GetCurrentProcessId(JNIEnv *env, jobject obj) {
    jlong thread_id = getpid();
    return thread_id;
}

JNIEXPORT jlong JNICALL
Java_systools_SysInfo_GetParentProcessId(JNIEnv *env, jobject obj) {
    jlong thread_id = getppid();
    return thread_id;
}

JNIEXPORT jstring JNICALL
Java_systools_SysInfo_GetProcessName(JNIEnv *env, jobject obj, jlong paramLong) {
    char* name = (char*) calloc(1024, sizeof (char));
    if (name) {
        sprintf(name, "/proc/%ld/cmdline", paramLong);
        FILE* f = fopen(name, "r");
        if (f) {
            size_t size;
            size = fread(name, sizeof (char), 1024, f);
            if (size > 0) {
                if ('\n' == name[size - 1])
                    name[size - 1] = '\0';
            }
            fclose(f);
        }
    }
    return (*env)->NewStringUTF(env, name);

}

JNIEXPORT jstring JNICALL
Java_systools_SysInfo_GetProcessIdString(JNIEnv *env, jobject obj, jlong paramLong) {
    char* name = (char*) calloc(1024, sizeof (char));
    if (name) {
        sprintf(name, "/proc/%ld/cmdline", paramLong);
        FILE* f = fopen(name, "r");
        if (f) {
            size_t size;
            size = fread(name, sizeof (char), 1024, f);
            if (size > 0) {
                if ('\n' == name[size - 1])
                    name[size - 1] = '\0';
            }
            fclose(f);
        } else {
            return 0;
        }
    }
    return (*env)->NewStringUTF(env, name);
}

long read_stat(int p_type, int t_type, long pid) {
    char buffer[4096], *p, *q;
    int len;
    long retval = 0;
    // t_type: process = 0, thread 1
    if (t_type == 0)
        sprintf(buffer, "/proc/%ld/stat", pid);
    else
        sprintf(buffer, "/proc/self/task/%ld/stat", pid);
    FILE* fd = fopen(buffer, "r");
    if (!fd)
        return 0;
    len = fread(buffer, sizeof (char), sizeof (buffer) - 1, fd);
    fclose(fd);
    if ((q = strrchr(buffer, ')')) == NULL) {
        return 0;
    }
    *q = '\0';
    p = q + 1;
    p = skip_token(p); /* skip state */
    p = skip_token(p); /* skip ppid */
    p = skip_token(p); /* skip pgrp */
    p = skip_token(p); /* skip session */
    p = skip_token(p); /* skip tty */
    p = skip_token(p); /* skip tty pgrp */
    p = skip_token(p); /* skip flags */
    p = skip_token(p); /* skip min flt */
    p = skip_token(p); /* skip cmin flt */
    p = skip_token(p); /* skip maj flt */
    p = skip_token(p); /* skip cmaj flt */
    // p_type: user time = 0, kernel time 1
    if (p_type == 0) {
        retval = strtoul(p, &p, 10); /* utime */
        p = skip_token(p); /* stime */
    } else {
        p = skip_token(p); /* utime */
        retval = strtoul(p, &p, 10); /* stime */
    }
    return retval;
}

JNIEXPORT jlong JNICALL
Java_systools_SysInfo_GetSysUsedTime(JNIEnv *env, jobject obj) {
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
    return cpu_time[0]+cpu_time[1]+cpu_time[2];
}

JNIEXPORT jlong JNICALL
Java_systools_SysInfo_GetSysIdleTime(JNIEnv *env, jobject obj) {
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
    return cpu_time[3];
}

JNIEXPORT jlong JNICALL
Java_systools_SysInfo_GetThreadKernelTime(JNIEnv *env, jobject obj, jlong paramLong) {
    return read_stat(1, 1, paramLong);
}

JNIEXPORT jlong JNICALL
Java_systools_SysInfo_GetThreadUserTime(JNIEnv *env, jobject obj, jlong paramLong) {
    return read_stat(0, 1, paramLong);
}

JNIEXPORT jlong JNICALL
Java_systools_SysInfo_GetCurrentThreadKernelTime(JNIEnv *env, jobject obj) {
    pid_t thread_id = syscall(SYS_gettid);
    return read_stat(1, 1, thread_id);
}

JNIEXPORT jlong JNICALL
Java_systools_SysInfo_GetCurrentThreadUserTime(JNIEnv *env, jobject obj) {
    pid_t thread_id = syscall(SYS_gettid);
    return read_stat(0, 1, thread_id);
}

JNIEXPORT jlong JNICALL
Java_systools_SysInfo_GetProcessKernelTime(JNIEnv *env, jobject obj, jlong paramLong) {
    return read_stat(1, 0, paramLong);
}

JNIEXPORT jlong JNICALL
Java_systools_SysInfo_GetProcessUserTime(JNIEnv *env, jobject obj, jlong paramLong) {
    return read_stat(0, 0, paramLong);
}

JNIEXPORT jlong JNICALL
Java_systools_SysInfo_GetProcessPageFaults(JNIEnv *env, jobject obj, jlong paramLong) {
    return 0;
}

JNIEXPORT jlong JNICALL
Java_systools_SysInfo_GetCurrentProcessPageFaults(JNIEnv *env, jobject obj) {
    jlong thread_id = getpid();
    return 0;
}

JNIEXPORT jlong JNICALL
Java_systools_SysInfo_GetCurrentProcessKernelTime(JNIEnv *env, jobject obj) {
    jlong proc_id = getpid();
    return read_stat(1, 0, proc_id);
}

JNIEXPORT jlong JNICALL
Java_systools_SysInfo_GetCurrentProcessUserTime(JNIEnv *env, jobject obj) {
    jlong proc_id = getpid();
    return read_stat(0, 0, proc_id);
}

JNIEXPORT jlong JNICALL
Java_systools_SysInfo_GetProcessMem(JNIEnv *env, jobject obj, jlong paramLong) {
    long rss = 0L;
    FILE* fp = NULL;
    char name[128];
    sprintf(name, "/proc/%ld/statm", paramLong);
    if ((fp = fopen(name, "r")) == NULL)
        return (size_t) 0L; /* Can't open? */
    if (fscanf(fp, "%*s%ld", &rss) != 1) {
        fclose(fp);
        return (size_t) 0L; /* Can't read? */
    }
    fclose(fp);
    return (size_t) rss * (size_t) sysconf(_SC_PAGESIZE);
}

JNIEXPORT jlong JNICALL
Java_systools_SysInfo_GetCurrentProcessMem(JNIEnv *env, jobject obj) {
    long rss = 0L;
    FILE* fp = NULL;
    if ((fp = fopen("/proc/self/statm", "r")) == NULL)
        return (size_t) 0L; /* Can't open? */
    if (fscanf(fp, "%*s%ld", &rss) != 1) {
        fclose(fp);
        return (size_t) 0L; /* Can't read? */
    }
    fclose(fp);
    return (size_t) rss * (size_t) sysconf(_SC_PAGESIZE);
}

JNIEXPORT jlong JNICALL
Java_systools_SysInfo_GetSysVirtualMem(JNIEnv *env, jobject obj) {
    int page_size = getpagesize();
    long pages_avail = get_phys_pages();
    return (jlong) (page_size * pages_avail);
}

JNIEXPORT jlong JNICALL
Java_systools_SysInfo_GetSysPhysicalMem(JNIEnv *env, jobject obj) {

    long pages = sysconf(_SC_PHYS_PAGES);
    long page_size = sysconf(_SC_PAGE_SIZE);
    return pages * page_size;
}

JNIEXPORT jlong JNICALL
Java_systools_SysInfo_GetSysUsedVirtualMem(JNIEnv *env, jobject obj) {
    struct rusage r_usage;
    getrusage(RUSAGE_SELF, &r_usage);
    return r_usage.ru_maxrss;
}

JNIEXPORT jlong JNICALL
Java_systools_SysInfo_GetSysPageFaults(JNIEnv *env, jobject obj) {
    return 0;
}

#define NANOSEC 1000000000 
#define MICROSEC  1000000

unsigned long
gethrtime(void) {
    struct timespec ts;

    if (clock_gettime(CLOCK_MONOTONIC_RAW, &ts) != 0) {
        return (-1);
    }
    return ((ts.tv_sec * NANOSEC) + ts.tv_nsec);
}

JNIEXPORT jlong JNICALL
Java_systools_SysInfo_GetTimeNanos(JNIEnv *env, jobject obj) {
    return gethrtime();
}

JNIEXPORT jlong JNICALL
Java_systools_SysInfo_GetTimeMicros(JNIEnv *env, jobject obj) {
    struct timespec ts;

    if (clock_gettime(CLOCK_MONOTONIC_RAW, &ts) != 0) {
        return (-1);
    }
    return ((ts.tv_sec * MICROSEC) + ts.tv_nsec);

}

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

/*
 * read /proc data into the passed struct pstat
 * returns 0 on success, -1 on error
 */
int get_thread_usage(const pid_t pid, struct pstat* result) {
    char buffer[4096], *p, *q;
    int len, i;
    long retval = 0;
    long int rss;    
    struct timeval thistime;
    
    gettimeofday(&result->time_value, 0);    
    
    sprintf(buffer, "/proc/self/task/%ld/stat", pid);
    FILE* fd = fopen(buffer, "r");
    if (!fd)
        return 0;
    len = fread(buffer, sizeof (char), sizeof (buffer) - 1, fd);
    fclose(fd);
    if ((q = strrchr(buffer, ')')) == NULL) {
        return 0;
    }
    *q = '\0';
    p = q + 1;
    p = skip_token(p); /* skip state */
    p = skip_token(p); /* skip ppid */
    p = skip_token(p); /* skip pgrp */
    p = skip_token(p); /* skip session */
    p = skip_token(p); /* skip tty */
    p = skip_token(p); /* skip tty pgrp */
    p = skip_token(p); /* skip flags */
    p = skip_token(p); /* skip min flt */
    p = skip_token(p); /* skip cmin flt */
    p = skip_token(p); /* skip maj flt */
    p = skip_token(p); /* skip cmaj flt */    
    result->utime_ticks = strtoul(p, &p, 10); /* utime */
    result->utime_ticks += strtoul(p, &p, 10); /* utime */
    // result->stime_ticks = strtoul(p, &p, 10); /* stime */
    // result->cutime_ticks = strtoul(p, &p, 10); /* cutime */
    // result->cstime_ticks = strtoul(p, &p, 10); /* cstime */    
    p = skip_token(p); /* skip priority */
    p = skip_token(p); /* skip nice */
    
    p = skip_token(p); /* skip priority */
    p = skip_token(p); /* skip nice */
    p = skip_token(p); /* skip num_threads */
    p = skip_token(p); /* skip itrealvalue */
    p = skip_token(p); /* skip starttime */
    p = skip_token(p); /* skip vsize */
    p = skip_token(p); /* skip itrealvalue */
    rss += strtoul(p, &p, 10); /* stime */
    result->rss = rss * getpagesize();

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

    for (i = 0; i < 10; i++)
        result->cpu_total_time += cpu_time[i];

    return 0;
}

int get_thread_cpu(const pid_t pid) {
    char buffer[4096], *p, *q;
    int len, i;
    double uptime, seconds;
    long int cputime, starttime, hertz;
    
    sprintf(buffer, "/proc/uptime");
    FILE* ft = fopen(buffer, "r");
    if (!ft) 
        return 0;
    len = fread(buffer, sizeof (char), sizeof (buffer) - 1, ft);
    fclose(ft);
    q = buffer;
    *q = '\0';
    p = q + 1;
    uptime = strtold(p, &p);
    sprintf(buffer, "/proc/self/task/%ld/stat", pid);
    FILE* fd = fopen(buffer, "r");
    if (!fd)
        return 0;
    len = fread(buffer, sizeof (char), sizeof (buffer) - 1, fd);
    fclose(fd);
    if ((q = strrchr(buffer, ')')) == NULL) {
        return 0;
    }
    *q = '\0';
    p = q + 1;
    p = skip_token(p); /* skip state */
    p = skip_token(p); /* skip ppid */
    p = skip_token(p); /* skip pgrp */
    p = skip_token(p); /* skip session */
    p = skip_token(p); /* skip tty */
    p = skip_token(p); /* skip tty pgrp */
    p = skip_token(p); /* skip flags */
    p = skip_token(p); /* skip min flt */
    p = skip_token(p); /* skip cmin flt */
    p = skip_token(p); /* skip maj flt */
    p = skip_token(p); /* skip cmaj flt */
    cputime = strtoul(p, &p, 10); /* utime */
    cputime += strtoul(p, &p, 10); /* stime */
    cputime += strtoul(p, &p, 10); /* cutime */
    cputime += strtoul(p, &p, 10); /* cstime */
    p = skip_token(p); /* skip priority */
    p = skip_token(p); /* skip nice */
    
    p = skip_token(p); /* skip priority */
    p = skip_token(p); /* skip nice */
    p = skip_token(p); /* skip num_threads */
    p = skip_token(p); /* skip itrealvalue */
    starttime = strtoul(p, &p, 10); /* skip starttime */
    
    hertz = sysconf(_SC_CLK_TCK);    
    seconds = uptime - (starttime / hertz);
    return (jlong) roundl(100 * ((cputime / hertz) / seconds));
}

int get_process_cpu(const pid_t pid) {
    char buffer[4096], *p, *q;
    int len, i;
    double uptime, seconds;
    long int cputime, starttime, hertz;
    
    sprintf(buffer, "/proc/uptime");
    FILE* ft = fopen(buffer, "r");
    if (!ft) 
        return 0;
    len = fread(buffer, sizeof (char), sizeof (buffer) - 1, ft);
    fclose(ft);
    q = buffer;
    *q = '\0';
    p = q + 1;
    uptime = strtold(p, &p);
    sprintf(buffer, "/proc/%ld/stat", pid);
    FILE* fd = fopen(buffer, "r");
    if (!fd)
        return 0;
    len = fread(buffer, sizeof (char), sizeof (buffer) - 1, fd);
    fclose(fd);
    if ((q = strrchr(buffer, ')')) == NULL) {
        return 0;
    }
    *q = '\0';
    p = q + 1;
    p = skip_token(p); /* skip state */
    p = skip_token(p); /* skip ppid */
    p = skip_token(p); /* skip pgrp */
    p = skip_token(p); /* skip session */
    p = skip_token(p); /* skip tty */
    p = skip_token(p); /* skip tty pgrp */
    p = skip_token(p); /* skip flags */
    p = skip_token(p); /* skip min flt */
    p = skip_token(p); /* skip cmin flt */
    p = skip_token(p); /* skip maj flt */
    p = skip_token(p); /* skip cmaj flt */
    cputime = strtoul(p, &p, 10); /* utime */
    cputime += strtoul(p, &p, 10); /* stime */
    cputime += strtoul(p, &p, 10); /* cutime */
    cputime += strtoul(p, &p, 10); /* cstime */
    p = skip_token(p); /* skip priority */
    p = skip_token(p); /* skip nice */
    
    p = skip_token(p); /* skip priority */
    p = skip_token(p); /* skip nice */
    p = skip_token(p); /* skip num_threads */
    p = skip_token(p); /* skip itrealvalue */
    starttime = strtoul(p, &p, 10); /* starttime */
    
    hertz = sysconf(_SC_CLK_TCK);
    seconds = uptime - (starttime / hertz);
    return (jlong) roundl(100 * ((cputime / hertz) / seconds));
}

/*
 * read /proc data into the passed struct pstat
 * returns 0 on success, -1 on error
 */
int get_process_usage(const pid_t pid, struct pstat* result) {
    char buffer[4096], *p, *q;
    int len, i;
    long retval = 0;
    long int rss;
    struct timeval thistime;
    
    gettimeofday(&result->time_value, 0);        
    sprintf(buffer, "/proc/%ld/stat", pid);
    FILE* fd = fopen(buffer, "r");
    if (!fd)
        return 0;
    len = fread(buffer, sizeof (char), sizeof (buffer) - 1, fd);
    fclose(fd);
    if ((q = strrchr(buffer, ')')) == NULL) {
        return 0;
    }
    *q = '\0';
    p = q + 1;
    p = skip_token(p); /* skip state */
    p = skip_token(p); /* skip ppid */
    p = skip_token(p); /* skip pgrp */
    p = skip_token(p); /* skip session */
    p = skip_token(p); /* skip tty */
    p = skip_token(p); /* skip tty pgrp */
    p = skip_token(p); /* skip flags */
    p = skip_token(p); /* skip min flt */
    p = skip_token(p); /* skip cmin flt */
    p = skip_token(p); /* skip maj flt */
    p = skip_token(p); /* skip cmaj flt */
    
    result->utime_ticks = strtoul(p, &p, 10); /* utime */
    result->stime_ticks = strtoul(p, &p, 10); /* stime */
    result->cutime_ticks = strtoul(p, &p, 10); /* cutime */
    result->cstime_ticks = strtoul(p, &p, 10); /* cstime */        
    p = skip_token(p); /* skip priority */
    p = skip_token(p); /* skip nice */
    
    p = skip_token(p); /* skip priority */
    p = skip_token(p); /* skip nice */
    p = skip_token(p); /* skip num_threads */
    p = skip_token(p); /* skip itrealvalue */
    p = skip_token(p); /* skip starttime */
    p = skip_token(p); /* skip vsize */
    p = skip_token(p); /* skip itrealvalue */
    rss += strtoul(p, &p, 10); /* stime */
    result->utime_ticks = retval;
    result->rss = rss * getpagesize();

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
    return 0;
}

/*
 * calculates the elapsed CPU usage between 2 measuring points. in percent
 */
void calc_cpu_usage_pct(const struct pstat* cur_usage,
        const struct pstat* last_usage,
        double* ucpu_usage, double* scpu_usage) {
    const long unsigned int total_time_diff = cur_usage->cpu_total_time -
            last_usage->cpu_total_time;

    *ucpu_usage = 100 * (((cur_usage->utime_ticks + cur_usage->stime_ticks)
            - (last_usage->utime_ticks + last_usage->stime_ticks))
            / (double) total_time_diff);

    *scpu_usage = 100 * ((((cur_usage->cutime_ticks + cur_usage->cstime_ticks)
            - (last_usage->cutime_ticks + last_usage->cstime_ticks))) /
            (double) total_time_diff);
}

/*
 * calculates the elapsed CPU usage between 2 measuring points in ticks
 */
void calc_cpu_usage(const struct pstat* cur_usage,
        const struct pstat* last_usage,
        long unsigned int* ucpu_usage,
        long unsigned int* scpu_usage) {

    *ucpu_usage = (cur_usage->utime_ticks + cur_usage->stime_ticks) -
            (last_usage->utime_ticks + last_usage->stime_ticks);

    *scpu_usage = (cur_usage->cutime_ticks + cur_usage->cstime_ticks) -
            (last_usage->cutime_ticks + last_usage->cstime_ticks);
}

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
    
    for (i = 0; i < 6; i++)
        result->cpu_total_time += cpu_time[i];

    return 0;
}

JNIEXPORT jlong JNICALL
Java_systools_SysInfo_GetTotalPercentUsedCPU(JNIEnv *env, jobject obj) {
    struct pstat b_usage, e_usage;
    double idle_delta, total_delta;
    jlong total;

    get_total_usage(&b_usage);
    usleep(100);    
    get_total_usage(&e_usage);
    idle_delta = e_usage.utime_ticks - b_usage.utime_ticks;
    total_delta = e_usage.cpu_total_time - b_usage.cpu_total_time;
    // total = 100 * (1.0 - idle_delta/total_delta);         
    total = (idle_delta / total_delta) * 100;    
    return total;       
}


JNIEXPORT jlong JNICALL
Java_systools_SysInfo_GetThreadPercentUsedCPU(JNIEnv *env, jobject obj, jlong paramLong) {    
    return get_thread_cpu(paramLong);
}

JNIEXPORT jlong JNICALL
Java_systools_SysInfo_GetProcessPercentUsedCPU(JNIEnv *env, jobject obj, jlong paramLong) {    
    return get_process_cpu(paramLong);
}

JNIEXPORT jlong JNICALL
Java_systools_SysInfo_GetProcessPercentUsedCPUX(JNIEnv *env, jobject obj, jlong paramLong) {
    struct pstat b_usage, e_usage;
    struct timeval timediff;
    unsigned long elapsed;
    double pcpu;

    get_process_usage(paramLong, &b_usage);
    usleep(100);
    get_process_usage(paramLong, &e_usage);
    timersub(&e_usage.time_value, &b_usage.time_value, &timediff);
    elapsed = timediff.tv_sec * HZ + (timediff.tv_usec * HZ) / 1000000;
    if (elapsed <= 0)
    {
	elapsed = 1;
    }
    if ((pcpu = (e_usage.utime_ticks - b_usage.utime_ticks) / (double)elapsed) < 0.0001)
    {
        pcpu = 0;
    }     
    return (jlong) roundl(pcpu * 100.0);
}

JNIEXPORT jlong JNICALL
Java_systools_SysInfo_GetThreadPercentUsedCPUX(JNIEnv *env, jobject obj, jlong paramLong) {
    struct pstat b_usage, e_usage;
    struct timeval timediff;
    unsigned long elapsed;
    double pcpu;

    get_thread_usage(paramLong, &b_usage);
    usleep(100);
    get_thread_usage(paramLong, &e_usage);
    timersub(&e_usage.time_value, &b_usage.time_value, &timediff);
    elapsed = timediff.tv_sec * HZ + (timediff.tv_usec * HZ) / 1000000;
    if (elapsed <= 0)
    {
	elapsed = 1;
    }
    if ((pcpu = (e_usage.utime_ticks - b_usage.utime_ticks) / (double)elapsed) < 0.0001)
    {
        pcpu = 0;
    }         
    return (jlong) roundl(pcpu * 100.0);
}

JNIEXPORT jlong JNICALL
Java_systools_SysInfo_GetActiveCPUCount(JNIEnv *env, jobject obj) {
    return sysconf(_SC_NPROCESSORS_ONLN);
}

JNIEXPORT jlong JNICALL
Java_systools_SysInfo_GetUUID(JNIEnv *env, jobject obj, jbyteArray paramArrayOfByte) {
    uuid_t uuid;
    uuid_generate_time_safe(uuid);
    jbyte *pbyte = (*env)->GetByteArrayElements(env, paramArrayOfByte, 0);
    int uuid_size = sizeof (uuid);
    int i;
    for (i = 0; i < uuid_size; i++) {
        pbyte[i] = uuid[i];
    }
    (*env)->ReleaseByteArrayElements(env, paramArrayOfByte, pbyte, 0);
    return sizeof (uuid);
}

JNIEXPORT jlong JNICALL
Java_systools_SysInfo_GetProcessHandles(JNIEnv *env, jobject obj, jlong paramLong) {
    return 0;
}

JNIEXPORT jlong JNICALL
Java_systools_SysInfo_GetCurrentProcessHandles(JNIEnv *env, jobject obj) {
    return 0;
}

JNIEXPORT jstring JNICALL
Java_systools_SysInfo_GetEnvVar(JNIEnv *env, jobject obj, jstring paramString) {
    const char *nativeString = (*env)->GetStringUTFChars(env, paramString, 0);
    char *envValue = getenv(nativeString);
    (*env)->ReleaseStringUTFChars(env, paramString, nativeString);
    return (*env)->NewStringUTF(env, envValue);
}

JNIEXPORT jobjectArray JNICALL
Java_systools_SysInfo_GetAllEnvVar(JNIEnv *env, jobject obj) {
    char **envValues;
    jobjectArray ret;
    int i, count;
    jstring values[4096];
    count = 0;
    for (envValues = environ; *envValues; envValues++) {
        values[count] = (jstring)(*env)->NewStringUTF(env, *envValues);
        count++;    
    }
    if (count > 0) {
        ret = (jobjectArray) (*env)->NewObjectArray(env, count, (*env)->FindClass(env, "java/lang/String"), (*env)->NewStringUTF(env, ""));
        
        envValues = environ;
        for (i = 0; i < count; i++) {            
            (*env)->SetObjectArrayElement(env, ret, i, (jstring) values[i]);
            envValues++;
        }
    } else ret = (jobjectArray)(*env)->NewObjectArray(env, 0, (*env)->FindClass(env, "java/lang/String"), (*env)->NewStringUTF(env, ""));
    return ret;
}

JNIEXPORT jstring JNICALL
Java_systools_SysInfo_GetVersion(JNIEnv *env, jobject obj) {
    char* name = (char*) calloc(1024, sizeof (char));
    
    if (name) {
        FILE* f = fopen("/proc/version", "r");
        if (f) {
            size_t size;
            size = fread(name, sizeof (char), 1024, f);
            if (size > 0) {
                if ('\n' == name[size - 1])
                    name[size - 1] = '\0';
            }
            fclose(f);
        }
    }
    return (*env)->NewStringUTF(env, name);
}


