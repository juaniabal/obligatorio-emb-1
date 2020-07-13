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
#include <stdio.h>
#include <string.h>

void prendoAnillo(ws2812_t color){
    int i;
    ws2812_t aux[8];
    for(i=0 ; i<8 ; i++){
        aux[i] = color;
    }
    WS2812_send(aux,8);
}

void apagoAnillo(){
    int i;
    ws2812_t aux[8];
    for(i=0 ; i<8 ; i++){
        aux[i] = BLACK;
    }
    WS2812_send(aux,8);
}

void medirtemperatura() {
    uint16_t voltaje = 0; //voltaje=un número desde 0 a 1023
    float grados = 0;
    int i = 0;
    float total = 0;
    for (i = 0; i < 5; i++) {
        ADC1_ChannelSelect(TempVol);
        ADC1_SoftwareTriggerEnable();
        vTaskDelay(pdMS_TO_TICKS(250));
        prendoAnillo(BLUE);
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
    if(total >= 37){
        prendoAnillo(RED);          
    }
    else{
        prendoAnillo(GREEN);
    }
    uint8_t redondeado[16];
    sprintf(redondeado, "%.1f\n", total); //En "redondeado" queda una cadena con el voltaje.
    USB_sendS(redondeado);  
    vTaskDelay(pdMS_TO_TICKS(2000));
    apagoAnillo();
}

/* *****************************************************************************
 End of File
 */
