/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

/* This section lists the other files that are included in this file.
 */
// <editor-fold defaultstate="collapsed" desc="Include Files">
#include "buttons.h"
#include <stdbool.h>
#include "../../mcc_generated_files/pin_manager.h"

// </editor-fold>

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */
// <editor-fold defaultstate="collapsed" desc="File Scope or Global Data">
    bool flag1 = false; 
    bool flag2 = false;
// </editor-fold>
/* ************************************************************************** */
/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */
/* ************************************************************************** */
// <editor-fold defaultstate="collapsed" desc="Interface Functions">
    void setTrueButton1(){
        flag1=true;
    }
    void resetButton1(){
        flag1=false;
    }
    bool getButton1(){
        return flag1;
    }
    void setTrueButton2(){
        flag2=true;
    }
    void resetButton2(){
        flag2=false;
    }
    bool getButton2(){
        return flag2;
    }
// </editor-fold>
/* *****************************************************************************
 End of File
 */
