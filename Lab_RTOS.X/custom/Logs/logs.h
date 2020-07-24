/* ************************************************************************** */
/** Descriptive File Name

  @Company
     UCUDAL

  @File Name
    logs.h


  @Description
 Contiene las funcionalidades ligadas a los logs
 */
/* ************************************************************************** */
#ifndef LOGS_H    
#define LOGS_H

#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include "../GPS/GPS.h"
#include <inttypes.h>

#define LOGS 200

typedef struct {//id registro es la posicion
    time_t time;
    uint8_t *ubicacion;
    float temp;//
} logger;

static logger  logsEvents[LOGS];
static uint8_t logPosition =0;


    
void WriteLogs();
void AddLog(logger event);
void cleanLog();

#endif