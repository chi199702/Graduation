
#include <sys/time.h>
#include <stddef.h>
#include <stdio.h>


typedef struct {
  int running;
  double seconds;
  double u_seconds;
  struct timeval Start;
  struct timeval Stop;
} Timer;


void timer_reset(Timer * const kTimer);

void timer_start(Timer * const kTimer);

void timer_stop(Timer * const kTimer);

void timer_restart(Timer * const kTimer);


void timer_print_sec(Timer * const kTimer, const char *remark);

void timer_print_usec(Timer * const kTimer, const char *remark);

void timer_print_iter_sec(Timer * const kTimer, int iters, const char *remark);