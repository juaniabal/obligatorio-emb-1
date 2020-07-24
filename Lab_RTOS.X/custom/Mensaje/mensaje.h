/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.h

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

#ifndef mensajee    /* Guard against multiple inclusion */
#define mensajee

#include <time.h>
#include <stdint.h>

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

/* This section lists the other files that are included in this file.
 */

/* TODO:  Include other files here if needed. */







    // *****************************************************************************
    // *****************************************************************************
    // Section: Interface Functions
    // *****************************************************************************
    // *****************************************************************************
    
    void envioMensaje(uint16_t id, struct tm hora, uint8_t pos, uint16_t temp, uint8_t phone);




#endif /* _EXAMPLE_FILE_NAME_H */

/* *****************************************************************************
 End of File
 */
