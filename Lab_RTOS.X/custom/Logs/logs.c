#include "logs.h"
#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include "../../mcc_generated_files/adc1.h"


/**
 * @Function
 *  WriteLogs()
 *
 * @Summary
 *   Función que envía toda la información almacenada en la lista de
 *  "eventos" que tenemos al USB. 
 * 
 */
void WriteLogs(){
    uint8_t i = 0;
    char registro[2];
    char logWriter[200];
    char fecha[50];
    char temp[12];
    if(logPosition == 0){
        USB_sendS("No hay logs registrados.");
    }
    while(i<logPosition){
         memset(logWriter, 0, sizeof(logWriter) );
         memset(registro, 0, sizeof(registro) );  
         memset(fecha, 0, sizeof(fecha) ); 
         memset(temp, 0, sizeof(temp) ); 
         
         strcpy(logWriter,"Registro ");
        if(i==0){
            strcpy(registro,"0");
        }else{
            sprintf(registro, "%d", i);
        }
        strcat(logWriter,registro);

        strcat(logWriter," ");
        strcpy(fecha,ctime(&logsEvents[i].time));
        strcat(logWriter,fecha);
        
        strcat(logWriter," ");
        strcat(logWriter,logsEvents[i].ubicacion);
        
        strcat(logWriter," ");
        sprintf(temp,"%d",logsEvents[i].temp);
        strcat(logWriter,temp);      
        
        strcat(logWriter,"\n");

        USB_sendS(logWriter);
        
        i++;
    }
}
/**
 * @Function
 *  AddLog(logger event)
 *
 * @Summary
 *   Función agrega eventos a la lista de los logs
 * 
 * @Remarks
 *   Si se agregan mas eventos de la cantidad permitida, no seran agregados.   
 * 
 *  * @Param:  event: es el evento donde se almacena lo ocurrido
 *          
 */
void AddLog(logger event){
    if(logPosition<=LOGS){        
        logsEvents[logPosition] = event; 
        logPosition++;
    }
}

void cleanLog(){
    if(logPosition == 0){
        USB_sendS("Los logs ya se encuentran vacios.\n");
    } else {
        logPosition = 0;
        USB_sendS("Se han borrado todos los registros.\n");
    }
}