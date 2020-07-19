// <editor-fold defaultstate="collapsed" desc="Include Files">

#include "UI.h"
#include "../LEDsRGB/WS2812.h"

#include "../../mcc_generated_files/rtcc.h"

#include "../../freeRTOS/include/FreeRTOS.h"
#include "../../mcc_generated_files/adc1.h"
#include "../Logs/logs.h"

#include <stdio.h>
#include <string.h>

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="File Scope or Global Data">
   extern uint8_t umbral1 = 37;
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Local Functions">
 

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Interface Functions">

void UI_menuTask( void* p_param) { //preguntar como hacer para que log.idregistro = id;
    UI_MENU_STATES s_state_menuTask = UI_MENU_STATE_MAIN;
    uint8_t inputBuffer[50];
    struct tm auxTM;
    bool dataValid;
    uint8_t id[10];
    uint8_t phone[50];
    uint8_t umbral[10];
    logger log;
    uint8_t i = 0; 
    //char logWriter[45];
    //char idRegistroLog[5];
    
    while( 1 ) {
        if( USB_isConnected() ) {
            switch( s_state_menuTask ) {
                case UI_MENU_STATE_MAIN:
                    USB_sendS("\nMENU PRINCIPAL\n");
                    USB_sendS("1_ Setear ID\n");
                    USB_sendS("2_ Consultar ID\n");
                    USB_sendS("3_ Setear Umbral\n");
                    USB_sendS("4_ Consultar umbral\n");
                    USB_sendS("5_ Registrar telefono\n");
                    USB_sendS("6_ Cambiar telefono\n");
                    USB_sendS("7_ Imprimir logs\n");
                    s_state_menuTask = UI_MENU_STATE_WAIT_INPUT;
                    
                    // Intentionally fall through

                case UI_MENU_STATE_WAIT_INPUT:
                    USB_receive(inputBuffer, sizeof (inputBuffer));

                    USB_sendS("\n");
                    switch( inputBuffer[0] ) {
                      
                        case '1':
                            if( RTCC_TimeGet(&auxTM) ) {
                                do {
                                    USB_sendS("Ingrese ID: ");
                                    USB_receive(id,sizeof(id));
                                    
                                    //sprintf(idRegistroLog, "%d", id);
                                    

                                    /*if(logPosition<=LOGS){
                                        logsEvents[logPosition] = log; 
                                        logPosition++;
                                    }*/

                                    //log.temp = 37.0;
                                    
                                    
                                    USB_sendS("\n");
                                    dataValid = true;
                                    log.temp = atof(id);
                                    
                                    AddLog(log);
                                }while( !dataValid );

                                RTCC_TimeSet(&auxTM);
                                                                
                                
                                //
                                    
                                //AddLog(log);
                                USB_sendS("ID configurado exitosamente\n");
                            }
                            else {
                                USB_sendS("Error, intente nuevamente\n");
                            }
                            break;
                            // </editor-fold>
                           
                        case '2':
                            if( RTCC_TimeGet(&auxTM) ) {
                                USB_sendS("ID es:\n");
                                
                                USB_sendS(id);
                            }
                            else {
                                USB_sendS("Error, intente nuevamente\n");
                            }
                            break;
                        case '3':
                            if( RTCC_TimeGet(&auxTM) ) {
                                do {
                                    
                                    USB_sendS("Nuevo umbral:");
                                    USB_receive(umbral,sizeof(umbral));
                                    USB_sendS("\n");
                                    dataValid = true;
                                }while( !dataValid );
                                umbral1 = atof(umbral);
                                
                                RTCC_TimeSet(&auxTM);
                                USB_sendS("Umbral configurado exitosamente\n");
                            }
                            else {
                                USB_sendS("Error, intente nuevamente\n");
                            }
                            break;
                          
                        case '4':
                            if( RTCC_TimeGet(&auxTM) ) {
                                USB_sendS("El umbral es: \n");
                                
                                //USB_sendS(umbral);
                                //vTaskDelay(pdMS_TO_TICKS(30));
                                char umbral2[5];
                                sprintf(umbral2, "%d", umbral1);
                                //USB_sendS("Consultar umbral2:\n");
                                USB_sendS(umbral2);
                            }
                            else {
                                USB_sendS("Error, intente nuevamente\n");
                            }
                            break;
                        case '5':
                            if( RTCC_TimeGet(&auxTM) ) {
                                do {
                                    USB_sendS("Ingrese Telefono registrado: ");
                                    USB_receive(phone,sizeof(phone));
                                    USB_sendS("\n");
                                    dataValid = true;
                                }while( !dataValid );

                                
                                RTCC_TimeSet(&auxTM);
                                USB_sendS("Telefono configurado exitosamente\n");
                            }
                            else {
                                USB_sendS("Error, intente nuevamente\n");
                            }
                            break;
                        case '6':
                            if( RTCC_TimeGet(&auxTM) ) {
                                USB_sendS("Consultar telefono registrado:\n");
                                
                                USB_sendS(phone);
                            }
                            else {
                                USB_sendS("Error, intente nuevamente\n");
                            }
                            break;                          
                        case '7':
                            if( RTCC_TimeGet(&auxTM) ) {
                                //POSICIONLOGS = 0;
                                
                                WriteLogs();
                                
                                /*
                                while(i<=logPosition)
                                {
                                    USB_sendS("a");                          
                                    memset(logWriter, 0, sizeof(logWriter) );
                                    
                                    strcpy(logWriter,"Registro ");
                                    
                                    USB_sendS(logWriter);
                                    
                                    sprintf(idRegistroLog, "%f", logsEvents[i]);
                                    
                                    strcat(logWriter,idRegistroLog);
                                    USB_sendS(logWriter);
                                    //USB_sendS(WriteLogs(logsEvents[i]));
                                    i++;
                                }
                                i=0;*/
                            }
                            else {
                                USB_sendS("Error, intente nuevamente\n");
                            }
                            break;                                
                        default:
                            USB_sendS("Opci�n no v�lida, intente nuevamente\n");
                            break;
                    }
                    s_state_menuTask = UI_MENU_STATE_MAIN;
                    break;
            }
        }
        else if( s_state_menuTask != UI_MENU_STATE_MAIN ) {
            s_state_menuTask = UI_MENU_STATE_MAIN;
        }
        else {
            vTaskDelay(pdMS_TO_TICKS(3000));
        }
    }
}
void BTN_taskCheck(void *p_param){
    
    while(1){
        vTaskDelay(pdMS_TO_TICKS(400));
        if (getButton1()) { 
            
            medirtemperatura(umbral1);
            resetButton1();
        }  
    }
}

// </editor-fold>
// </editor-fold>


