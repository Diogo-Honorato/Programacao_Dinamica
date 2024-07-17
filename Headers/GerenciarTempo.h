#ifndef _GERENCIAR_TEMPO_H_
#define _GERENCIAR_TEMPO_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>
 
void timeval_subtract (struct timeval*, struct timeval*, struct timeval*);
void getUsageNow (double*, double*);
double joinTimes (time_t, suseconds_t);
void printTimes (double, double, double, double);

#endif