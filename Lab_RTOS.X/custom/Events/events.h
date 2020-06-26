

#ifndef EVENTS_H    /* Guard against multiple inclusion */
#define EVENTS_H

// <editor-fold defaultstate="collapsed" desc="Include Files">

#include "../LEDsRGB/WS2812.h"

#include <stdint.h>
#include <stdbool.h>
#include <time.h>

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Constants and Macros">

#define EVE_EVENT_QTY   5

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Data Types">

typedef enum {
    EVE_COMMAND_NOT_CONF = -1,
    EVE_COMMAND_OFF = 0,
    EVE_COMMAND_ON = 1,
} EVE_COMMANDS;

typedef struct {
    EVE_COMMANDS command;
    uint8_t param;
    WS2812_STD_COLORS color;
    time_t time;
} eve_event_t;

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Global Data">
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Interface Functions">

bool EVE_areAnyAvailable( void );

bool EVE_addEvent( EVE_COMMANDS p_command, uint8_t p_ledIndex, WS2812_STD_COLORS p_ledColor, struct tm p_dateTime );

bool EVE_deleteEvent( uint8_t p_eventIndex );

bool EVE_getActiveEvent( uint8_t p_eventIndex, eve_event_t* p_event );

void EVE_eventsTask( void* p_param );

// </editor-fold>

#endif /* EVENTS_H */
