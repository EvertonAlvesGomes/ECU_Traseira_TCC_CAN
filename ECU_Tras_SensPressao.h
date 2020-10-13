/* ECU_Tras_SensPressao.h
 *  Implementação do sensor de pressão.
 *  Autor: Everton A. Gomes
 *  Data: 19/09/2020
*/

#ifndef _ECU_TRAS_SENSPRESSAO_H
#define _ECU_TRAS_SENSPRESSAO_H

//********************************************************************************
//                             #defines
//********************************************************************************

#define ADC_RANGE       4096      //Range do ADC de 12 bits
#define ADC_PRESS_CHANNEL     0         //Canal do AD a ser utilizado pelo sensor de pressão

//********************************************************************************
//                             #includes
//********************************************************************************

#include "ECU_Tras_ADC.h"

//********************************************************************************
//                             Variáveis
//********************************************************************************

float pressao=0;

//********************************************************************************
//                             Funções
//********************************************************************************

void sens_pressao_meas_config(){
  adcConfig();
  ecu_tras_adc_enable_channel(ADC_PRESS_CHANNEL);
}

float calcula_pressao(){
  pressao = 10*12.5*(((float)adcReadChannel(ADC_CH0))/ADC_RANGE - 0.1);
  return pressao;
}

#endif
