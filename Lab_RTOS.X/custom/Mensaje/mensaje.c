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

#include "mensaje.h"
#include "../../freeRTOS/include/FreeRTOS.h"
#include "../../mcc_generated_files/rtcc.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
/* This section lists the other files that are included in this file.
 */

/* TODO:  Include other files here if needed. */




/* ************************************************************************** */
/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */
/* ************************************************************************** */


void envioMensaje(uint16_t id, struct tm hora, uint8_t pos, uint16_t temp, uint8_t phone){
    char logWriter[200];
    char fecha[50];
    char temp1[12];
    uint8_t numero[12];
    int8_t res;
    time_t hour;
    hour = mktime(&hora);
    memset(logWriter, 0, sizeof (logWriter));

    strcat(logWriter, id);
    USB_sendS(logWriter);
    strcat(logWriter, " ");
    strcpy(fecha, ctime(&hour));
    strcat(logWriter, fecha);
    strcat(logWriter, " ");
    strcat(logWriter, pos);
    strcat(logWriter, " ");
    sprintf(temp1, "%d", temp);
    strcat(logWriter, temp1);
    USB_sendS(logWriter);
    memset(numero, 0, sizeof (numero));
    strcat(numero, "\"");
    strcat(numero, phone);
    strcat(numero, "\"");
    USB_sendS(numero);
    /*res = SIM808_sendSMS(numero, logWriter);
    if(res == 1){
        USB_sendS("se envio");
    }
    else{
        USB_sendS("no envio");
    }*/
   
    
    
}


/* *****************************************************************************
 End of File
 */
