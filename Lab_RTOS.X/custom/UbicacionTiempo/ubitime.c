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

void obtenerUbicacionTiempo() {
    bool verifica = false;
    uint8_t gpss[100];
    uint8_t link[150];
    GPSPosition_t pos;
    struct tm hora;
    while (verifica != true) {
        SIM808_getNMEA(gpss);
        vTaskDelay(pdMS_TO_TICKS(100));
        verifica = SIM808_validateNMEAFrame(gpss);
        USB_sendS(gpss);
    }
    USB_sendS(gpss);
    /*
    GPS_getPosition(&pos, gpss);
    vTaskDelay(pdMS_TO_TICKS(100));
    GPS_getUTC(&hora, pos);
    vTaskDelay(pdMS_TO_TICKS(100));
    GPS_generateGoogleMaps(link,pos);*/
}



/* *****************************************************************************
 End of File
 */
