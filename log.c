#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

void log_time()
{
    char* time_str;
    time_t epoch;
    struct timeval tv_gettime;
    struct timespec ts_clock;
    struct tm local;

    gettimeofday(&tv_gettime, NULL);
    epoch = time(NULL);
    clock_gettime(CLOCK_REALTIME, &ts_clock);
    localtime_r(&epoch, &local);
    time_str = ctime(&epoch); 
    time_str[strlen(time_str) - 1] = 0;
    
    printf("%d %d %7d %2d %2d %2d %s\n", 
        epoch, 
        tv_gettime.tv_sec, 
        tv_gettime.tv_usec, 
        local.tm_hour,
        local.tm_min, 
        local.tm_sec, 
        time_str
    );
    free(time_str);
}

void log_loop(int delay_ms)
{
    struct timespec delay;
    delay.tv_sec = delay_ms/1000;
    delay.tv_nsec = (delay_ms % 1000) * 1e6;

    printf("gettimeofday(), tv_sec, tv_usec, \n");
    while(true) {
        log_time();
        clock_nanosleep(CLOCK_MONOTONIC, 0, &delay, NULL);
    }
}

int main(int argc, char** argv)
{
    int delay;

    if(argc == 2) {
        delay = atoi(argv[1]);
        log_loop(delay);
        return EXIT_SUCCESS;
    } else {
        fprintf(stderr, "%s <delay in ms>\n", argv[0]);
    }
    return EXIT_FAILURE;
}
