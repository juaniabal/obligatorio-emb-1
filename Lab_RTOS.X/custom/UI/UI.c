// <editor-fold defaultstate="collapsed" desc="Include Files">

#include "UI.h"
#include "../LEDsRGB/WS2812.h"

#include "../../mcc_generated_files/rtcc.h"

#include "../../freeRTOS/include/FreeRTOS.h"
#include "../../mcc_generated_files/adc1.h"
#include "../Logs/logs.h"
#include "../Mensaje/mensaje.h"

#include <stdio.h>
#include <string.h>

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="File Scope or Global Data">
    uint8_t umbral1 = 37;
    int parpadeo = 1;
    int positivo = 2;
    int negativo = 3;
    
    uint8_t pos[200];
    struct tm hora;
    float temp;
    
    uint8_t phone[50] = "098765432";
    uint8_t id[10] = "1234";


// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Local Functions">
 



/**
 * @Function
 *  UI_menuTask
 *
 * @Summary
 *   Función que despliega el menu al USB
 *   
 *          
 */
    // <editor-fold defaultstate="collapsed" desc="Interface Functions">
void UI_menuTask( void* p_param) { 
 // <editor-fold defaultstate="collapsed" desc="variables">
    UI_MENU_STATES s_state_menuTask = UI_MENU_STATE_MAIN;
    uint8_t inputBuffer[50];
    struct tm auxTM;
    bool dataValid;
    uint8_t umbral[10];
    //logger log;
    uint8_t i = 0; 
    uint8_t parp[10];
    uint8_t pos[10];
    uint8_t neg[10];
// </editor-fold>
    
    while( 1 ) {
        if( USB_isConnected() ) {
            switch( s_state_menuTask ) {
         // <editor-fold defaultstate="collapsed" desc="Opciones">
                case UI_MENU_STATE_MAIN:
                    USB_sendS("\nMENU PRINCIPAL\n");
                    USB_sendS("1_ Setear ID\n");
                    USB_sendS("2_ Consultar ID\n");
                    USB_sendS("3_ Setear Umbral\n");
                    USB_sendS("4_ Consultar umbral\n");
                    USB_sendS("5_ Registrar telefono\n");
                    USB_sendS("6_ Mostrar número de telefono\n");
                    USB_sendS("7_ Imprimir logs\n");
                    USB_sendS("8_ Borrar logs\n");
                    USB_sendS("9_ Configurar el color de los led en el parpadeo, cuando da positivo y cuando da negativo\n");
                    s_state_menuTask = UI_MENU_STATE_WAIT_INPUT;
                    
            // </editor-fold>
                     // <editor-fold defaultstate="collapsed" desc="Opcion elegida">
                case UI_MENU_STATE_WAIT_INPUT:
                    USB_receive(inputBuffer, sizeof (inputBuffer));

                    USB_sendS("\n");
                    switch( inputBuffer[0] ) {
                      
                        case '1':
                            if( RTCC_TimeGet(&auxTM) ) {
                                do {
                                    USB_sendS("Ingrese ID: ");
                                    USB_receive(id,sizeof(id));

                                    USB_sendS("\n");
                                    dataValid = true;

                                }while( !dataValid );

                                RTCC_TimeSet(&auxTM);
                                USB_sendS("ID configurado exitosamente\n");
                            }
                            else {
                                USB_sendS("Error, intente nuevamente\n");
                            }
                            break;
                           
                           
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
                                
                                WriteLogs();

                            }
                            else {
                                USB_sendS("Error, intente nuevamente\n");
                            }
                            break;
                        case '8':
                            if (RTCC_TimeGet(&auxTM)) {
                                cleanLog();                                
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
                            USB_sendS("Opción no válida, intente nuevamente\n");
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
    // </editor-fold>
}
// <editor-fold defaultstate="collapsed" desc="BTN check">
 


/**
 * @Function
 *  BTN_taskCheck
 *
 * @Summary
 *   Función agrega eventos a la lista de los logs, obteniendo al mismo tiempo
 * la temperatura y  ubicacion de la placa
 * 
 *          
 */
void BTN_taskCheck(void *p_param){
    logger prueba;
    while(1) {
        vTaskDelay(pdMS_TO_TICKS(400));
        if (getButton1()) {
            vTaskDelay(pdMS_TO_TICKS(400));
            resetButton1(); //se setea el flag en false
            medirtemperatura(umbral1, parpadeo, positivo, negativo, &temp);
            if (!getButton1()) {
              /*uint16_t redondeado[16];
                sprintf(redondeado, "%.1f\n", temp);
                USB_sendS(redondeado);*/
                vTaskDelay(pdMS_TO_TICKS(40));
                obtenerUbicacionTiempo(&pos, &hora);
                prueba.temp = temp;
                prueba.ubicacion = &pos;
                prueba.time = mktime(&hora);
                AddLog(prueba);
                vTaskDelay(pdMS_TO_TICKS(40));
                if(temp > umbral1){
                  
                    envioMensaje(&id,hora,&pos,temp,&phone);
                }
            }
            else{
                USB_sendS("Medición cancelada\n");
            }
            resetButton1();
        }  
    }
}


// </editor-fold>

// </editor-fold>


