#include "logs.h"
#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include "../../mcc_generated_files/adc1.h"



void WriteLogs(){//PROTEGER CON SEMAFORO
    uint8_t i = 0;
    char registro[2];
    char logWriter[200];
    char fecha[50];
    char temp[12];
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
        strcat(logWriter,"\n");

        strcat(logWriter,"Fecha: ");
        strcpy(fecha,ctime(&logsEvents[i].time));
        strcat(fecha,"\n");

        strcat(logWriter,fecha);
        
        strcat(logWriter,"Temp: ");
        sprintf(temp,"%d",logsEvents[i].temp);
        strcat(temp,"\n");
        strcat(logWriter,temp);
                 
        strcat(logWriter,"Ubicacion: ");
        strcat(logWriter,logsEvents[i].ubicacion);
         strcat(logWriter,"\n");
        strcat(logWriter,"-----");                       
        strcat(logWriter,"\n");
        
        USB_sendS(logWriter);
        
        i++;
    }
}
void AddLog(logger event){
    if(logPosition<=LOGS){        
        logsEvents[logPosition] = event; 
        logPosition++;
    }
}