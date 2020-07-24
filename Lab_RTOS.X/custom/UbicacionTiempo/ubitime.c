
// <editor-fold defaultstate="collapsed" desc="Include Files">
#include "../../freeRTOS/include/FreeRTOS.h"
#include "../../mcc_generated_files/rtcc.h"
#include <stdio.h>
#include <string.h>
#include "ubitime.h"
#include <stdbool.h>
#include "../GPS/GPS.h"
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Interface Functions">
void obtenerUbicacionTiempo(uint8_t *link, struct tm *hora) {
    bool verifica = false;
    uint8_t gpss[] =  "+CGNSINF: 1,1,20210714222033.000,-34.884820,-56.069692,33.800,0.15,196.6,1,,2.5,2.7,1.0,,10,4,,,4,,";
    GPSPosition_t pos;
    /*
    while (verifica != true) {
        SIM808_getNMEA(gpss);
        vTaskDelay(pdMS_TO_TICKS(100));
        verifica = SIM808_validateNMEAFrame(gpss);
        USB_sendS(gpss);
    }*/
    GPS_getPosition(&pos, &gpss[0]);
    GPS_getUTC(hora, gpss);
    GPS_generateGoogleMaps(link,pos);
}
// </editor-fold>
