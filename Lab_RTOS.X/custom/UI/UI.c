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
    uint8_t umbral1 = 37;
    int parpadeo = 1;
    int positivo = 2;
    int negativo = 3;
    
    uint8_t pos[] = "maps.google.com/maps?q=-34.884820,-56.069692";
    struct tm hora;


// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Local Functions">
 

// </editor-fold>


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
    uint8_t parp[10];
    uint8_t pos[10];
    uint8_t neg[10];
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
                    USB_sendS("8_ Borrar logs\n");
                    USB_sendS("9_ Configurar el color de los led en el parpadeo, cuando da positivo y cuando da negativo\n");
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
                                   /* log.temp = atof(id);
                                    
                                    AddLog(log);*/
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
                                USB_sendS("El ID es:\n");
                                
                                USB_sendS(id);
                            }
                            else {
                                USB_sendS("Error, intente nuevamente\n");
                            }
                            break;
                        case '3':
                            if( RTCC_TimeGet(&auxTM) ) {
                                do {
                                    
                                    USB_sendS("Ingrese un nuevo umbral:");
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
                                char umbral2[5];
                                sprintf(umbral2, "%d", umbral1);
                                
                                USB_sendS(umbral2);
                            }
                            else {
                                USB_sendS("Error, intente nuevamente\n");
                            }
                            break;
                        case '5':
                            if( RTCC_TimeGet(&auxTM) ) {
                                do {
                                    USB_sendS("Ingrese un numero telefonico: ");
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
                                USB_sendS("El telefono registrado es:\n");
                                
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
                        case '8':
                            if (RTCC_TimeGet(&auxTM)) {
                                USB_sendS("Se han borrado todos los registros.:\n");

                                
                            } else {
                                USB_sendS("Error, intente nuevamente\n");
                            }
                            break;    
                        case '9':
                            if( RTCC_TimeGet(&auxTM) ) {
                                do {
                                    USB_sendS("Para configurar el parpadeo\n");
                                    USB_sendS("Ingrese 1 para el color Azul, 2 Rojo, 3 Verde, 4 Blanco y si ingresa uno diferente no tendra color.");
                                    USB_receive(parp,sizeof(parp));
                                    USB_sendS("\n");
                                    dataValid = true;
                                }while( !dataValid );
                                parpadeo = atof(parp);
                                dataValid = false;
                                do {
                                    USB_sendS("Para configurar el Positivo\n");
                                    USB_sendS("Ingrese 1 para el color Azul, 2 Rojo, 3 Verde, 4 Blanco y si ingresa uno diferente no tendra color.\n");
                                    USB_receive(pos,sizeof(pos));
                                    USB_sendS("\n");
                                    dataValid = true;
                                }while( !dataValid );
                                positivo = atof(pos);
                                dataValid = false;
                                do {
                                    USB_sendS("Para configurar el Negativo\n");
                                    USB_sendS("Ingrese 1 para el color Azul, 2 Rojo, 3 Verde, 4 Blanco y si ingresa uno diferente no tendra color.\n");
                                    USB_receive(neg,sizeof(neg));
                                    USB_sendS("\n");
                                    dataValid = true;
                                }while( !dataValid );
                                negativo = atof(neg);
                                
                                RTCC_TimeSet(&auxTM);
                                USB_sendS("Colores configurados exitosamente\n");
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
    
    logger prueba;
    while(1){
        vTaskDelay(pdMS_TO_TICKS(400));
        if (getButton1()) { 
            uint16_t temp;
            temp = medirtemperatura(umbral1, parpadeo, positivo, negativo);
            vTaskDelay(pdMS_TO_TICKS(40));
            obtenerUbicacionTiempo(&pos, &hora);
            /*
            uint16_t redondeado[16];
            sprintf(redondeado, "%.1d\n", temp); //En "redondeado" queda una cadena con el voltaje.
             USB_sendS(redondeado);*/
            prueba.temp = temp;
            prueba.ubicacion = "http://maps.google.com/maps?q=-34.884820,-56.069692";
            prueba.time = mktime(&hora);
            AddLog(prueba);
            resetButton1();
        }  
    }
}

// </editor-fold>
// </editor-fold>


