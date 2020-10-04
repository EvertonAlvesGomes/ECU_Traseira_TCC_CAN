/* ECU_Tras_Comb.h
 *  Implementação da leitura de combustível para ECU Traseira.
 *  Autor: Everton A. Gomes
 *  Data: 03/10/2020
*/

#ifndef _ECU_TRAS_COMB_H
#define _ECU_TRAS_COMB_H


//********************************************************************************
//                             #includes
//********************************************************************************

#include "ECU_Tras_PIO.h"

//********************************************************************************
//                             #defines
//********************************************************************************
#define NIVEL_1                     1
#define NIVEL_2                     2
#define NIVEL_3                     3
#define NIVEL_4                     4
#define NIVEL_5                     5
#define NIVEL_6                     6
#define PIN_NIVEL_1                 25      //PC25 - Digital Pin 5
#define PIN_NIVEL_2                 24      //PC24 - Digital Pin 6
#define PIN_NIVEL_3                 23      //PC23 - Digital Pin 7
#define PIN_NIVEL_4                 22      //PC22 - Digital Pin 8
#define PIN_NIVEL_5                 21      //PC21 - Digital Pin 9
#define PIN_NIVEL_6                 29      //PC29 - Digital Pin 10


//********************************************************************************
//                             Variáveis
//********************************************************************************
uint8_t nivel_1, nivel_2, nivel_3, nivel_4, nivel_5, nivel_6;

//********************************************************************************
//                             Funções
//********************************************************************************
void ecu_tras_comb_config_input_pins(){

  ecu_tras_pio_init();
  
  //Configurando os pinos como I/O:
  ecu_tras_pio_enable_pin_controlling(PIN_NIVEL_1);
  ecu_tras_pio_enable_pin_controlling(PIN_NIVEL_2);
  ecu_tras_pio_enable_pin_controlling(PIN_NIVEL_3);
  ecu_tras_pio_enable_pin_controlling(PIN_NIVEL_4);
  ecu_tras_pio_enable_pin_controlling(PIN_NIVEL_5);
  ecu_tras_pio_enable_pin_controlling(PIN_NIVEL_6);

  //Configurando os pinos como entradas digitais:
  ecu_tras_pio_config_input(PIN_NIVEL_1);
  ecu_tras_pio_config_input(PIN_NIVEL_2);
  ecu_tras_pio_config_input(PIN_NIVEL_3);
  ecu_tras_pio_config_input(PIN_NIVEL_4);
  ecu_tras_pio_config_input(PIN_NIVEL_5);
  ecu_tras_pio_config_input(PIN_NIVEL_6);

  //Habilitando resistor de pull-up interno:
  ecu_tras_pio_enable_pullup_resistor(PIN_NIVEL_1);
  ecu_tras_pio_enable_pullup_resistor(PIN_NIVEL_2);
  ecu_tras_pio_enable_pullup_resistor(PIN_NIVEL_3);
  ecu_tras_pio_enable_pullup_resistor(PIN_NIVEL_4);
  ecu_tras_pio_enable_pullup_resistor(PIN_NIVEL_5);
  ecu_tras_pio_enable_pullup_resistor(PIN_NIVEL_6);
}

/*
 * ecu_tras_comb_calcula_nivel()
 * Lê as entradas digitais correspondentes aos níveis de combustível e retorna o nível atual.
 * O nível atual é aquele cujo pino de entrada está em nível LOW.
 * Se nenhum nível for detectado, a função retorna 0xFF (255).
 */
uint8_t ecu_tras_comb_calcula_nivel(){
  nivel_1 = ecu_tras_pio_read_pin(PIN_NIVEL_1);
  nivel_2 = ecu_tras_pio_read_pin(PIN_NIVEL_2);
  nivel_3 = ecu_tras_pio_read_pin(PIN_NIVEL_3);
  nivel_4 = ecu_tras_pio_read_pin(PIN_NIVEL_4);
  nivel_5 = ecu_tras_pio_read_pin(PIN_NIVEL_5);
  nivel_6 = ecu_tras_pio_read_pin(PIN_NIVEL_6);

  if(!nivel_1) return NIVEL_1;
  else{
    if(!nivel_2) return NIVEL_2;
    else {
      if(!nivel_3) return NIVEL_3;
      else
        if(!nivel_4) return NIVEL_4;
        else
          if(!nivel_5) return NIVEL_5;
          else
            if(!nivel_6) return NIVEL_6;
            else
              return 0xFF;
    }
  }
  
}

#endif
