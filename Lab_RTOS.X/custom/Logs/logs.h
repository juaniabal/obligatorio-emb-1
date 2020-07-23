
#ifndef LOGS_H    
#define LOGS_H

#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include "../GPS/GPS.h"
#include <inttypes.h>

#define LOGS 5

typedef struct {//id registro es la posicion
    time_t time;
    uint8_t* ubicacion;
    uint16_t temp;//
} logger;
//static uint8_t ejemplologsEvents[3];
static logger logsEvents[LOGS];
static uint8_t logPosition =0;


    
void WriteLogs();
void AddLog(logger event);
#endif