
// <editor-fold defaultstate="collapsed" desc="Include Files">
#include "../LEDsRGB/WS2812.h"
#include "../../freeRTOS/include/FreeRTOS.h"
#include "../../mcc_generated_files/adc1.h"
#include "temperatura.h"
#include <stdio.h>
#include <string.h>
// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="Interface Functions">
void prendoAnillo(int color) {
    int i;
    ws2812_t aux[8];
    switch (color) {
        case 1:
            for (i = 0; i < 8; i++) {
                aux[i] = BLUE;
            }
            WS2812_send(aux, 8);
            break;
        case 2:
            for (i = 0; i < 8; i++) {
                aux[i] = RED;
            }
            WS2812_send(aux, 8);
            break;
        case 3:
            for (i = 0; i < 8; i++) {
                aux[i] = GREEN;
            }
            WS2812_send(aux, 8);
            break;
        case 4:
            for (i = 0; i < 8; i++) {
                aux[i] = WHITE;
            }
            WS2812_send(aux, 8);
            break;
        default:
            for (i = 0; i < 8; i++) {
                aux[i] = BLACK;
            }
            WS2812_send(aux, 8);
            break;
    }
}
/**
 * @Function
 *  apagoAnillo()
 *
 * @Summary
 *   Función que "apaga" todos los leds o en otras palabras setea a cada led
 *  del anillo el color negro.
 * 
 *          
 */
void apagoAnillo() {
    int i;
    ws2812_t aux[8];
    for (i = 0; i < 8; i++) {
        aux[i] = BLACK;
    }
    WS2812_send(aux, 8);
}
/**
 * @Function
 *   medirtemperatura(int umbral, int parpadeo, int positivo, int negativo)
 *
 * @Summary
 *   Función devuelve la temperatura calculada y enciende los leds que se
 * encuentran en el anillo. Se encienden cuando se obtiene un resultado
 * y cuando esta consiguiendo el promedio
 *  
 * 
 *  * @Param:   umbral: es el numero con el que se compara la temperatura 
 *          conseguida a traves del voltaje de la placa.  
 *          
 *              parpadeo: es un numero que indica el color a prender mientras esta
 *          haciendo el promedio de las temperaturas
 *              positivo: es un numero que indica el color si el numero del
 *          umbral es menor al del promedio de la temperatura obtenida
 *              negativo: es un numero que indica el color si el numero del
 *          umbral es mayor al del promedio de la temperatura obtenida         
 */
void medirtemperatura(int umbral, int parpadeo, int positivo, int negativo, uint16_t *temp) {
    uint16_t voltaje = 0; 
    float grados = 0;
    int i = 0;
    uint16_t total = 0;
    for (i = 0; i < 5; i++) {
        ADC1_ChannelSelect(TempVol);
        ADC1_SoftwareTriggerEnable();
        vTaskDelay(pdMS_TO_TICKS(250));
        prendoAnillo(parpadeo);
        ADC1_SoftwareTriggerDisable();
        while (!ADC1_IsConversionComplete(TempVol)) {
            vTaskDelay(pdMS_TO_TICKS(1));
        }
        voltaje = ADC1_ConversionResultGet(TempVol);
        grados = (32 + (voltaje * 0.00977517106));
        total += grados;
        ADC1_ChannelSelect(TempVol);
        ADC1_SoftwareTriggerEnable();
        vTaskDelay(pdMS_TO_TICKS(250));
        apagoAnillo();
        ADC1_SoftwareTriggerDisable();
        while (!ADC1_IsConversionComplete(TempVol)) {
            vTaskDelay(pdMS_TO_TICKS(1));
        }
        voltaje = ADC1_ConversionResultGet(TempVol);
        grados = (32 + (voltaje * 0.00977517106));
        total += grados;
    }
    total = total / 10;
    vTaskDelay(pdMS_TO_TICKS(100));
    //USB_sendS(redondeado);
    if (total >= umbral) {
        prendoAnillo(positivo);
    } else {
        prendoAnillo(negativo);
    }
    vTaskDelay(pdMS_TO_TICKS(2000));
    apagoAnillo();
    *temp = total;
}
// </editor-fold>
/* *****************************************************************************
 End of File
 */
