// <editor-fold defaultstate="collapsed" desc="Include Files">

#include "UI.h"
#include "../Events/events.h"
#include "../LEDsRGB/WS2812.h"

#include "../../mcc_generated_files/rtcc.h"

#include "../../freeRTOS/include/FreeRTOS.h"

#include "../../mcc_generated_files/adc1.h"

#include <stdio.h>
#include <string.h>

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="File Scope or Global Data">


// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Local Functions">


// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Interface Functions">

void UI_menuTask( void* p_param ) {
    UI_MENU_STATES s_state_menuTask = UI_MENU_STATE_MAIN;
    uint8_t outBuffer[50];
    uint8_t inputBuffer[50];
    struct tm auxTM;
    struct tm* auxTMptr;
    uint16_t auxInt;
    bool dataValid;
    eve_event_t auxEvent;

    while( 1 ) {
        if( USB_isConnected() ) {
            switch( s_state_menuTask ) {
                case UI_MENU_STATE_MAIN:
                    USB_sendS("\nMENU PRINCIPAL\n");
                    USB_sendS("1_ Setear fecha/hora\n");
                    USB_sendS("2_ Consultar fecha/hora\n");
                    USB_sendS("3_ Agregar evento de calendario\n");
                    USB_sendS("4_ Eliminar evento de calendario\n");
                    USB_sendS("5_ Consultar lista de eventos activos\n");
                    s_state_menuTask = UI_MENU_STATE_WAIT_INPUT;
                    // Intentionally fall through

                case UI_MENU_STATE_WAIT_INPUT:
                    USB_receive(inputBuffer, sizeof (inputBuffer));
                    USB_sendS("\n");
                    switch( inputBuffer[0] ) {
                            // <editor-fold defaultstate="collapsed" desc="Setear fecha/hora">
                        case '1':
                            if( RTCC_TimeGet(&auxTM) ) {
                                do {
                                    USB_sendS("Ingrese la fecha (formato DD/MM/AAAA): ");
                                    USB_receive(inputBuffer, sizeof (inputBuffer));
                                    sscanf(inputBuffer, "%d/%d/%d", &(auxTM.tm_mday), &(auxTM.tm_mon), &auxInt);
                                    dataValid = true;
                                    dataValid = dataValid && ((1 <= auxTM.tm_mday) && (auxTM.tm_mday <= 31));
                                    dataValid = dataValid && ((1 <= auxTM.tm_mon) && (auxTM.tm_mon <= 12));
                                    dataValid = dataValid && (1900 <= auxInt);
                                    auxTM.tm_year = auxInt - 1900;
                                    auxTM.tm_mon--;

                                    USB_sendS("\n");
                                }while( !dataValid );

                                do {
                                    USB_sendS("Ingrese la hora (formato HH:MM:SS - 24hs): ");
                                    USB_receive(inputBuffer, sizeof (inputBuffer));
                                    sscanf(inputBuffer, "%d:%d:%d", &(auxTM.tm_hour), &(auxTM.tm_min), &(auxTM.tm_sec));
                                    dataValid = true;
                                    dataValid = dataValid && ((0 <= auxTM.tm_hour) && (auxTM.tm_hour <= 24));
                                    dataValid = dataValid && ((0 <= auxTM.tm_min) && (auxTM.tm_min <= 59));
                                    dataValid = dataValid && ((0 <= auxTM.tm_sec) && (auxTM.tm_sec <= 59));

                                    USB_sendS("\n");
                                }while( !dataValid );

                                RTCC_TimeSet(&auxTM);
                                USB_sendS("Fecha/hora configurada exitosamente\n");
                            }
                            else {
                                USB_sendS("Error inesperado, acción no disponible\n");
                            }
                            break;
                            // </editor-fold>
                            // <editor-fold defaultstate="collapsed" desc="Consultar fecha/hora">
                        case '2':
                            if( RTCC_TimeGet(&auxTM) ) {
                                uint16_t voltaje; //voltaje=un número desde 0 a 1023
                                int i;
                                USB_sendS("La fecha y hora actual es:\n");                            
                                
                                for (i = 0; i<1 ; i++) {
                                    USB_sendS("PASO\n");
                           
                                    ADC1_ChannelSelect(TempVol);
                                    ADC1_SoftwareTriggerEnable();
                                    
                                    for (i = 0; i < 1000; i++) {
                                    }
                                    USB_sendS("PASO2\n");
                                    ADC1_SoftwareTriggerDisable();
                                    while (!ADC1_IsConversionComplete(TempVol)) {
                                        //delay del freertos
                                        voltaje += ADC1_ConversionResultGet(TempVol);
                                    }

                               
                                }

                                float grados=voltaje;//el num decimal es el resultado de dividir 10/1023
                                uint8_t redondeado[16];
                                sprintf(redondeado,"%.1f\n",grados); //En "redondeado" queda una cadena con el voltaje.

                                USB_sendS(redondeado);
                               // strftime(outBuffer, sizeof (outBuffer) - 1, "%d/%m/%Y - %H:%M:%S\n", &auxTM);
                                //USB_sendS(outBuffer);
                            
                            }
                            else {
                                USB_sendS("Error inesperado, información no disponible\n");
                            }
                            break;
                            // </editor-fold>

                            // <editor-fold defaultstate="collapsed" desc="Agregar evento de calendario">
                        case '3':
                            if( EVE_areAnyAvailable() ) {
                                // <editor-fold defaultstate="collapsed" desc="Elegir acción">
                                do {
                                    USB_sendS("¿Que acción desea realizar?\n");
                                    USB_sendS("1_ Encender LED\n");
                                    USB_sendS("2_ Apagar LED LED\n");
                                    USB_receive(inputBuffer, sizeof (inputBuffer));
                                    switch( inputBuffer[0] ) {
                                        case '1':
                                            auxEvent.command = EVE_COMMAND_ON;
                                            dataValid = true;
                                            break;
                                        case '2':
                                            auxEvent.command = EVE_COMMAND_OFF;
                                            dataValid = true;
                                            break;
                                        default:
                                            USB_sendS("Opción no válida\n");
                                            dataValid = false;
                                            break;
                                    }
                                }while( !dataValid );
                                USB_sendS("\n");
                                // </editor-fold>
                                // <editor-fold defaultstate="collapsed" desc="Elegir LED">
                                do {
                                    USB_sendS("¿Que LED desea ");
                                    USB_sendS((auxEvent.command == EVE_COMMAND_ON) ? ("encender") : ("apagar"));
                                    USB_sendS(" (del 0 al 7)?\n");
                                    USB_receive(inputBuffer, sizeof (inputBuffer));

                                    if( ('0' <= inputBuffer[0]) && (inputBuffer[0] <= '7') ) {
                                        auxEvent.param = inputBuffer[0] - '0';
                                    }
                                    else {
                                        dataValid = false;
                                    }
                                    USB_sendS("\n");
                                }while( !dataValid );
                                // </editor-fold>

                                if( auxEvent.command == EVE_COMMAND_ON ) {
                                    // <editor-fold defaultstate="collapsed" desc="Elegir color">
                                    do {
                                        USB_sendS("¿De que color desea que encienda el LED?\n");
                                        USB_sendS("1_ Blanco\n");
                                        USB_sendS("2_ Rojo\n");
                                        USB_sendS("3_ Azul\n");
                                        USB_sendS("4_ Verde\n");

                                        dataValid = true;
                                        USB_receive(inputBuffer, sizeof (inputBuffer));
                                        switch( inputBuffer[0] ) {
                                            case '1':
                                                auxEvent.color = WS2812_STD_COLOR_WHITE;
                                                break;
                                            case '2':
                                                auxEvent.color = WS2812_STD_COLOR_RED;
                                                break;
                                            case '3':
                                                auxEvent.color = WS2812_STD_COLOR_BLUE;
                                                break;
                                            case '4':
                                                auxEvent.color = WS2812_STD_COLOR_GREEN;
                                                break;
                                            default:
                                                USB_sendS("Opción no válida\n");
                                                dataValid = false;
                                                break;
                                        }
                                        USB_sendS("\n");
                                    }while( !dataValid );
                                    // </editor-fold>
                                }

                                // <editor-fold defaultstate="collapsed" desc="Ingresar fecha/hora">
                                do {
                                    USB_sendS("Ingrese la fecha (formato DD/MM/AAAA): ");
                                    USB_receive(inputBuffer, sizeof (inputBuffer));
                                    sscanf(inputBuffer, "%d/%d/%d", &(auxTM.tm_mday), &(auxTM.tm_mon), &auxInt);
                                    dataValid = true;
                                    dataValid = dataValid && ((1 <= auxTM.tm_mday) && (auxTM.tm_mday <= 31));
                                    dataValid = dataValid && ((1 <= auxTM.tm_mon) && (auxTM.tm_mon <= 12));
                                    dataValid = dataValid && (1900 <= auxInt);
                                    auxTM.tm_year = auxInt - 1900;
                                    auxTM.tm_mon--;

                                    USB_sendS("\n");
                                }while( !dataValid );

                                do {
                                    USB_sendS("Ingrese la hora (formato HH:MM:SS - 24hs): ");
                                    USB_receive(inputBuffer, sizeof (inputBuffer));
                                    sscanf(inputBuffer, "%d:%d:%d", &(auxTM.tm_hour), &(auxTM.tm_min), &(auxTM.tm_sec));
                                    dataValid = true;
                                    dataValid = dataValid && ((0 <= auxTM.tm_hour) && (auxTM.tm_hour <= 24));
                                    dataValid = dataValid && ((0 <= auxTM.tm_min) && (auxTM.tm_min <= 59));
                                    dataValid = dataValid && ((0 <= auxTM.tm_sec) && (auxTM.tm_sec <= 59));

                                    USB_sendS("\n");
                                }while( !dataValid );
                                // </editor-fold>

                                EVE_addEvent(auxEvent.command, auxEvent.param, auxEvent.color, auxTM);

                                USB_sendS("Evento configurado exitosamente\n");
                            }
                            else {
                                USB_sendS("No se pueden agregar más eventos\n");
                            }
                            break;
                            // </editor-fold>
                            // <editor-fold defaultstate="collapsed" desc="Eliminar evento de calendario">
                        case '4':
                            do {
                                USB_sendS("¿Que evento desea eliminar?\n");
                                USB_sendS("(Números entre el 1 y ");
                                memset(outBuffer, 0, sizeof (outBuffer));
                                sprintf(outBuffer, "%u)\n", EVE_EVENT_QTY);
                                USB_sendS(outBuffer);

                                USB_receive(inputBuffer, sizeof (inputBuffer));
                                USB_sendS("\n");
                                auxInt = atoi(inputBuffer);
                                if( (auxInt == 0) || (auxInt > EVE_EVENT_QTY) ) {
                                    dataValid = false;
                                    USB_sendS("Entrada no válida\n");
                                }
                                else {
                                    dataValid = true;
                                    if( EVE_deleteEvent(auxInt - 1) ) {
                                        USB_sendS("Evento eliminado correctamente\n");
                                    }
                                    else {
                                        USB_sendS("El evento seleccionado ya había sido eliminado\n");
                                    }
                                }
                            }while( !dataValid );
                            break;
                            // </editor-fold>
                            // <editor-fold defaultstate="collapsed" desc="Consultar lista de eventos activos">
                        case '5':
                            dataValid = false;
                            for( auxInt = 0; auxInt < EVE_EVENT_QTY; auxInt++ ) {
                                if( EVE_getActiveEvent(auxInt, &auxEvent) ) {
                                    dataValid = true;
                                    memset(outBuffer, 0, sizeof (outBuffer));
                                    sprintf(outBuffer, "%u_ ", auxInt + 1);
                                    USB_sendS(outBuffer);

                                    memset(outBuffer, 0, sizeof (outBuffer));
                                    if( auxEvent.command == EVE_COMMAND_OFF ) {
                                        sprintf(outBuffer, "Apagar LED %u", auxEvent.param);
                                        USB_sendS(outBuffer);
                                    }
                                    else {
                                        sprintf(outBuffer, "Encender LED %u color ", auxEvent.param);
                                        USB_sendS(outBuffer);
                                        switch( auxEvent.color ) {
                                            case WS2812_STD_COLOR_WHITE:
                                                USB_sendS("blanco");
                                                break;
                                            case WS2812_STD_COLOR_RED:
                                                USB_sendS("rojo");
                                                break;
                                            case WS2812_STD_COLOR_BLUE:
                                                USB_sendS("azul");
                                                break;
                                            case WS2812_STD_COLOR_GREEN:
                                                USB_sendS("verde");
                                                break;
                                        }
                                    }
                                    auxTMptr = gmtime(&(auxEvent.time));
                                    memset(outBuffer, 0, sizeof (outBuffer));
                                    strftime(outBuffer, sizeof (outBuffer) - 1, " el %d/%m/%Y a las %H:%M:%S\n", auxTMptr);
                                    USB_sendS(outBuffer);
                                }
                            }
                            if( !dataValid ) {
                                USB_sendS("No hay eventos activos\n");
                            }
                            break;
                            // </editor-fold>

                            // <editor-fold defaultstate="collapsed" desc="Opción no válida">
                        default:
                            USB_sendS("Opción no válida\n");
                            break;
                            // </editor-fold>
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

// </editor-fold>


