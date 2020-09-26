/* ECU_Tras_Peripheral_Deploying.h
 *  Implementação dos periféricos relativos aos sensores. Utilizar este arquivo somente com o CAN desabilitado
 *  relativos aos sensores.
 *  Autor: Everton A. Gomes
 *  Data: 19/09/2020
*/

#ifndef _ECU_TRAS_PERIPHERAL_DEPLOYING_H
#define _ECU_TRAS_PERIPHERAL_DEPLOYING_H

//********************************************************************************
//                             #includes
//********************************************************************************

#include "ECU_Tras_Defines.h"
#include "ECU_Tras_ADC.h"
#include "ECU_Tras_Timer.h"


#ifdef ENABLE_PERIPHERAL_DEPLOYING

//********************************************************************************
//                             Variáveis
//********************************************************************************



//********************************************************************************
//                             Funções
//********************************************************************************  
float ler_adc(){
  return adcRead();
}

uint32_t ler_timer_0_counter(){
  return *pTC_CV0;
}

uint32_t ler_timer_0_status(){
  return *pTC_SR0;
}


#endif    //ENABLE_CAN_DEPLOYING

#endif    //_ECU_TRAS_CAN_DEPLOYING_H
