/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.c

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

#include "../../freeRTOS/include/FreeRTOS.h"
#include "../../mcc_generated_files/rtcc.h"
#include <stdio.h>
#include <string.h>
#include "ubitime.h"
#include <stdbool.h>
#include "../GPS/GPS.h"

time_t horaDos;

/* This section lists the other files that are included in this file.
 */

/* TODO:  Include other files here if needed. */


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */






/* ************************************************************************** */
/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */
/* ************************************************************************** */

void obtenerUbicacionTiempo(GPSPosition_t *pos, struct tm *hora) {
    bool verifica = false;
    uint8_t gpss[] =  "+CGNSINF: 1,1,20200714222033.000,-34.884820,-56.069692,33.800,0.15,196.6,1,,2.5,2.7,1.0,,10,4,,,4,,";
    uint8_t link[50];
    hora->tm_year=120;
    hora->tm_mon=6;
    hora->tm_mday= 23;
    hora->tm_hour=03;
    hora->tm_min= 01;
    hora->tm_sec= 40;
    /*
    while (verifica != true) {
        SIM808_getNMEA(gpss);
        vTaskDelay(pdMS_TO_TICKS(100));
        verifica = SIM808_validateNMEAFrame(gpss);
        USB_sendS(gpss);
    }*/
   ///vTaskDelay(pdMS_TO_TICKS(6000));
     //pos.longitude = -56.069692;
     //pos.latitude = -34.884820;
    //USB_sendS(gpss);
    //vTaskDelay(pdMS_TO_TICKS(6000));
    //GPS_getPosition(pos, gpss);
    //vTaskDelay(pdMS_TO_TICKS(100));
   // GPS_getUTC(hora, gpss);
    vTaskDelay(pdMS_TO_TICKS(100));
    //RTCC_TimeSet(&time);
    //horaDos = mktime(&hora);
    //USB_sendS(ctime(&horaDos));
    //vTaskDelay(pdMS_TO_TICKS(100));
    //GPS_generateGoogleMaps(link,pos);
    //USB_sendS(link);
}



/* *****************************************************************************
 End of File
 */
