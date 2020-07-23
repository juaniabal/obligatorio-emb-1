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


#include "../LEDsRGB/WS2812.h"
#include "../../freeRTOS/include/FreeRTOS.h"
#include "../../mcc_generated_files/adc1.h"
#include "temperatura.h"
#include <stdio.h>
#include <string.h>

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

void apagoAnillo() {
    int i;
    ws2812_t aux[8];
    for (i = 0; i < 8; i++) {
        aux[i] = BLACK;
    }
    WS2812_send(aux, 8);
}

void medirtemperatura(int umbral, int parpadeo, int positivo, int negativo) {
    uint16_t voltaje = 0; //voltaje=un número desde 0 a 1023
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
    uint16_t redondeado[16];
    sprintf(redondeado, "%.1d\n", total); //En "redondeado" queda una cadena con el voltaje.
    USB_sendS(redondeado);
    vTaskDelay(pdMS_TO_TICKS(2000));
    apagoAnillo();
    obtenerUbicacionTiempo();
}

/* *****************************************************************************
 End of File
 */
