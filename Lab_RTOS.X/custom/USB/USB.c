// <editor-fold defaultstate="collapsed" desc="Include Files">

#include "USB.h"
#include "../../mcc_generated_files/usb/usb.h"
#include "../../mcc_generated_files/pin_manager.h"

#include "../../freeRTOS/include/FreeRTOS.h"
#include "../../freeRTOS/include/semphr.h"

#include <string.h>

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="File Scope or Global Data">

static SemaphoreHandle_t c_txInProgress;
static SemaphoreHandle_t c_waitingForRx;

static usb_rxDest_t c_rxDest = { .ptr = NULL };

static bool c_isConnected = false;

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Local Functions">


// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Interface Functions">

void USB_initialize( void ) {
    c_txInProgress = xSemaphoreCreateBinary();
    c_waitingForRx = xSemaphoreCreateBinary();
}

void USB_taskCheck( void* p_param ) {

    while( 1 ) {
        if( (USBGetDeviceState() >= CONFIGURED_STATE) && !USBIsDeviceSuspended() ) {
            CDCTxService();
            LEDB_SetHigh();
            c_isConnected = true;

            if( USBUSARTIsTxTrfReady() ) {
                xSemaphoreGive(c_txInProgress);
            }
            if( c_rxDest.ptr != NULL ) {
                c_rxDest.bytesReceived = getsUSBUSART(c_rxDest.ptr, c_rxDest.size);
                if( c_rxDest.bytesReceived > 0 ) {
                    xSemaphoreGive(c_waitingForRx);
                }
            }
        }
        else {
            LEDB_SetLow();
            c_isConnected = false;
        }
    }
}

void USB_send( uint8_t* p_src, uint8_t p_length ) {
    xSemaphoreTake(c_txInProgress, portMAX_DELAY);
    putUSBUSART(p_src, p_length);
    xSemaphoreTake(c_txInProgress, portMAX_DELAY);
}

void USB_sendS( uint8_t* p_src ) {
    USB_send(p_src, strlen(p_src));
}

uint8_t USB_receive( uint8_t* p_dst, uint8_t p_size ) {
    c_rxDest.ptr = p_dst;
    c_rxDest.size = p_size;
    xSemaphoreTake(c_waitingForRx, portMAX_DELAY);
    c_rxDest.ptr = NULL;
    p_dst[c_rxDest.bytesReceived] = '\0';
    return c_rxDest.bytesReceived;
}

bool USB_isConnected( void ) {
    return c_isConnected;
}

// </editor-fold>


