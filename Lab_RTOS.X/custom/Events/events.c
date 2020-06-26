
// <editor-fold defaultstate="collapsed" desc="Include Files">

#include "events.h"

#include <string.h>

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="File Scope or Global Data">

static eve_event_t c_events[EVE_EVENT_QTY];

static ws2812_t c_ledArray[WS2812_LED_QTY];

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Local Functions">

static eve_event_t* EVE_findEmpty( void ) {
    uint8_t i;

    for( i = 0; i < EVE_EVENT_QTY; i++ ) {
        if( c_events[i].command == EVE_COMMAND_NOT_CONF ) {
            return &c_events[i];
        }
    }
    return NULL;
}

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Interface Functions">

bool EVE_areAnyAvailable( void ) {
    return (EVE_findEmpty() != NULL);
}

bool EVE_addEvent( EVE_COMMANDS p_command, uint8_t p_ledIndex, WS2812_STD_COLORS p_ledColor, struct tm p_dateTime ) {
    eve_event_t* event;

    event = EVE_findEmpty();
    if( event != NULL ) {
        event->command = p_command;
        event->param = p_ledIndex;
        event->color = p_ledColor;
        event->time = mktime(&p_dateTime);
        return true;
    }
    else {
        return false;
    }
}

bool EVE_deleteEvent( uint8_t p_eventIndex ) {
    if( p_eventIndex < EVE_EVENT_QTY ) {
        if( c_events[p_eventIndex].command != EVE_COMMAND_NOT_CONF ) {
            c_events[p_eventIndex].command = EVE_COMMAND_NOT_CONF;
            return true;
        }
        else {
            return false;
        }
    }
    return false;
}

bool EVE_getActiveEvent( uint8_t p_eventIndex, eve_event_t* p_event ) {
    if( p_eventIndex == 0 ) {
        c_events[0] = (eve_event_t){ .command = EVE_COMMAND_ON };
    }
    if( p_eventIndex == 1 ) {
        c_events[1] = (eve_event_t){ .command = EVE_COMMAND_OFF };
    }
    if( c_events[p_eventIndex].command != EVE_COMMAND_NOT_CONF ) {
        memcpy((uint8_t*) p_event, (uint8_t*) & c_events[p_eventIndex], sizeof (eve_event_t));
        return true;
    }
    else {
        return false;
    }
}

void EVE_eventsTask( void* p_param ) {
    uint8_t eventIndex;
    struct tm currentTM;
    static time_t startingTime;

    memset((uint8_t*) c_ledArray, 0, sizeof (c_ledArray));
    WS2812_send(c_ledArray, WS2812_LED_QTY);
    memset((uint8_t*) c_events, 0, sizeof (c_events));

    // <editor-fold defaultstate="collapsed" desc="Configuracion de Test">
    //    RTCC_TimeGet(&currentTM);
    //    RTCC_TimeSet(&currentTM);
    //    startingTime = mktime(&currentTM);
    //
    //    c_events[0] = (eve_event_t){ EVE_COMMAND_ON, 2, WS2812_STD_COLOR_BLUE, startingTime + 5 };
    //    c_events[1] = (eve_event_t){ EVE_COMMAND_ON, 5, WS2812_STD_COLOR_GREEN, startingTime + 10 };
    //    c_events[2] = (eve_event_t){ EVE_COMMAND_OFF, 2, WS2812_STD_COLOR_GREEN, startingTime + 15 };

    // </editor-fold>

    while( 1 ) {
        for( eventIndex = 0; eventIndex < EVE_EVENT_QTY; eventIndex++ ) {
            if( c_events[eventIndex].command != EVE_COMMAND_NOT_CONF ) {
                RTCC_TimeGet(&currentTM);
                if( mktime(&currentTM) > c_events[eventIndex].time ) {
                    if( c_events[eventIndex].command == EVE_COMMAND_ON ) {
                        switch( c_events[eventIndex].color ) {
                            case WS2812_STD_COLOR_WHITE:
                                c_ledArray[c_events[eventIndex].param] = WHITE;
                                break;
                            case WS2812_STD_COLOR_RED:
                                c_ledArray[c_events[eventIndex].param] = RED;
                                break;
                            case WS2812_STD_COLOR_BLUE:
                                c_ledArray[c_events[eventIndex].param] = GREEN;
                                break;
                            case WS2812_STD_COLOR_GREEN:
                                c_ledArray[c_events[eventIndex].param] = BLUE;
                                break;
                        }
                    }
                    else {
                        c_ledArray[c_events[eventIndex].param] = BLACK;
                    }
                    c_events[eventIndex].command = EVE_COMMAND_NOT_CONF;
                    WS2812_send(c_ledArray, WS2812_LED_QTY);
                }
            }
        }
    }
}

// </editor-fold>


