/* ECU_Tras_Rpm.h
 *  Implementação da leitura de rotações por minuto (rpm).
 *  Autor: Everton A. Gomes
 *  Data: 07/10/2020
*/

/* Pinagem:
 * Pino digital 3 -> sinal de entrada
 * Pino digital 3 -> PC28
 */

/* Descrição:
 * Sinal digital é aplicado no pino 3 do Arduino. Usa-se uma interrupção por mudança de nível digital
 * do perifério PIO Controller para sinalizar que o millis() deve ser disparado. Após contagem de tempo
 * do millis(), calcula-se a frequência do sinal
 */

#ifndef _ECU_TRAS_RPM_H
#define _ECU_TRAS_RPM_H


//********************************************************************************
//                             #includes
//********************************************************************************

#include "ECU_Tras_Timer.h"
#include "ECU_Tras_PIO.h"
#include "ECU_Tras_PMC.h"


//********************************************************************************
//                             #defines
//********************************************************************************

#define RPM_PIN                 28      //Pino do micro para leitura do RPM (PC28 - Entrada digital 3)



//********************************************************************************
//                             Variáveis
//********************************************************************************

uint32_t ra2_atual, ra2_prev, tc2_sr, result2;
uint8_t pin_state = 0, pin_state_prev = 0;
uint32_t t1=0, t2=0, rpm=0;


//********************************************************************************
//                             Funções
//********************************************************************************

void ecu_tras_rpm_config(){
  /*
   * Configuração do pino de entrada:
   * - Habilita o controle PIO sobre o pino
   * - Configura o pino como entrada
   * - Habilita interrupção do PIOC
   * - Habilita interrupção por input change no pino de entrada do sinal
   */
  ecu_tras_pioc_enable_pin_controlling(RPM_PIN);
  ecu_tras_pioc_config_input(RPM_PIN);
//  ecu_tras_pioc_interrupt_enable(15);
//  ecu_tras_pioc_enable_interrupt_pin(RPM_PIN);    
}


uint32_t ecu_tras_rpm_calcula_rpm(){
  pin_state = ecu_tras_pioc_read_pin(RPM_PIN);
  if(pin_state == 1 && pin_state_prev == 0){
    //Se detectada borda de subida
    t2 = millis();
    rpm = (1000/(t2 - t1))*90; //calcula o rpm
    t1 = t2; //atualiza o tempo
  }
  pin_state_prev = pin_state; //atualiza o estado do pino
  return rpm;
}



#endif
