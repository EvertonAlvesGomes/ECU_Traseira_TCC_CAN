/* ECU_Tras_Rpm.h
 *  Implementação da leitura de rotações por minuto (rpm).
 *  Autor: Everton A. Gomes
 *  Data: 07/10/2020
*/

/* Pinagem:
 * Pino digital 3 -> sinal de entrada
 * Pino digital 3 -> PC28, Peripheral B, Signal TIOA7, TC2
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



//********************************************************************************
//                             Funções
//********************************************************************************

void ecu_tras_rpm_config(){
  /*
   * Configuração do pino de entrada:
   * - Desabilita o controle PIO sobre o pino, habilitando o controle pelo periférico Timer 2
   * - Seleciona a função periférica B
   * - Configura o pino como entrada
   */
  ecu_tras_pioc_disable_pio_controlling(RPM_PIN);
  ecu_tras_pioc_select_peripheral('B', RPM_PIN);
  ecu_tras_pioc_config_input(RPM_PIN);    

  ecu_tras_timer_timer2_config();
}

/* uint16_t calculaVelocidade()
 *  Retorna o valor da velocidade atual.
*/
uint16_t ecu_tras_rpm_calcula_rpm(){
  
  if(ra2_atual != ra2_prev){
    result2 = ra2_atual - ra2_prev;
    ra2_prev = ra2_atual;
  }
  return 42e6/result2;
  //return 1/(result*2/84e6); //retorna o valor da velocidade
  
}



#endif
