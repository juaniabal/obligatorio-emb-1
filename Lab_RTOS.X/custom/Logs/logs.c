#include "logs.h"
#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include "../../mcc_generated_files/adc1.h"



void WriteLogs(){//PROTEGER CON SEMAFORO?
    uint8_t i = 0;
    char logWriter[45];
    char tempLog[8];
    char registro[4];
    while(i<logPosition){
         memset(logWriter, 0, sizeof(logWriter) );
                                    
        strcpy(logWriter,"Registro ");
        if(i==0){
            strcpy(registro,"0");
        }else{
            sprintf(registro, "%d", i);
        }
        strcat(logWriter,registro);
        strcat(logWriter,"\n Temp: ");
                                    
        sprintf(tempLog, "%d", logsEvents[i].temp);
                                    
        strcat(logWriter,tempLog);
        USB_sendS(logWriter);
                                    
        i++;
    }
    i=0;
}
void AddLog(logger event){
    if(logPosition<=LOGS){        
        logsEvents[logPosition] = event; 
        logPosition++;
    }
}